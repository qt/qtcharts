use Cwd;
use Cwd 'abs_path';
use File::Basename;
use File::Copy;
use feature "switch";
use lib 'test/scripts';
use Jobs;

# read command line params
my $jobname = shift;

# read ini file
my $inifile = File::Basename::dirname($0) . "/jobs.ini";
my %job = Jobs::get($inifile, $jobname);

# set/get paths
my $root_path = abs_path();
my $bin_path = "$root_path/bin/";
my $reports_path = "test-reports";

# create reports path
mkdir $reports_path;

# setup environment for running tests
given ($job{'Platform'}) {
	
	when ("Win7") {
		$ENV{'PATH'} .= ";" . $job{'QtDir'} . "\\bin"; # Add qtdir to path
		$ENV{'PATH'} =~ s/\//\\/g; # replace / -> \
	}

	when ("Linux") {
		$ENV{'PATH'} = $job{'QtDir'} . "/bin:" . $ENV{'PATH'};
		$ENV{'DISPLAY'} = ":0.0";
	}
}	

# Go through all the files in the test folder
# autotest is an executable beginning with "tst_"
my $script_exit_status = 0;
opendir (TESTAPPDIR, "$bin_path") or die "Couldn't open test app dir";
@files = <TESTAPPDIR>;
while ($testapp = readdir TESTAPPDIR) {
    if (index($testapp, "tst_") == 0) {
        if (-x "$bin_path$testapp") {
            my $status = executeTestApp($testapp);
			if ($status != 0) {
				$script_exit_status = $status;
			}
        } else {
            #print "file $testapp not executable\n";
        }
    }
}
closedir TESTAPPDIR;

print "\n*** script exit status : $script_exit_status ***\n\n";
exit($script_exit_status);


sub executeTestApp($) {
    my $testapp = $_[0];
	
	# On OSX the actual test binary is in a sub folder
	my $cmd_postfix = "";
	if ($^O eq "darwin") {
		$cmd_postfix = "/Contents/MacOS/$testapp";
		$cmd_postfix = substr($cmd_postfix, 0, rindex($cmd_postfix, ".app"));
	}
	
    my $cmd = "$bin_path$testapp$cmd_postfix -xunitxml -o $reports_path/$testapp.xml";
    print "executing: $cmd\n";
    system($cmd);
	
	# From http://perldoc.perl.org/perlvar.html about $?:
	# The upper eight bits reflect specific error conditions encountered by the
    # program (the program's exit() value). The lower eight bits reflect
    # mode of failure, like signal death and core dump information.
    # See wait(2) for details. 
    my $exit_status = $? >> 8;
    print "\texit status: $exit_status\n";
	
	return $exit_status;
}
