use Cwd;
use Cwd 'abs_path';
use File::Basename;
use File::Copy;
use lib 'test/scripts';
use Jobs;

# read command line params
my $jobname = shift;

# read ini file
my $inifile = File::Basename::dirname($0) . "/jobs.ini";
my %job = Jobs::get($inifile, $jobname);

# set/get paths
my $root_path = abs_path();
my $test_path = "$root_path/bin/test/";
my $reports_path = "test-reports";

# create reports path
mkdir dirname($reports_path);

# Windows specific magic
if ($job{'Platform'} eq "Win7") {
	$ENV{'PATH'} .= ";" . $job{'QtDir'} . "\\bin"; # Add qtdir to path
	$ENV{'PATH'} .= ";" . $root_path . "\\bin"; # Add charts bin to path
	$ENV{'PATH'} =~ s/\//\\/g; # replace / -> \
}

my $script_exit_status = 0;

# Go through all the files in the test folder
# autotest is an executable beginning with "tst_"
opendir (TESTAPPDIR, "$test_path") or die "Couldn't open test app dir";
@files = <TESTAPPDIR>;
while ($testapp = readdir TESTAPPDIR) {
    if (index($testapp, "tst_") == 0) {
        if (-x "$test_path$testapp") {
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

print "\nscript exit status : $script_exit_status\n";
exit($script_exit_status);

sub executeTestApp($) {
    my $testapp = $_[0];
	
	# On OSX the actual test binary is in a sub folder
	my $cmd_postfix = "";
	if ($^O eq "darwin") {
		$cmd_postfix = "/Contents/MacOS/$testapp";
		$cmd_postfix = substr($cmd_postfix, 0, rindex($cmd_postfix, ".app"));
	}
	
    my $cmd = "$test_path$testapp$cmd_postfix -xunitxml -o $reports_path/$testapp.xml";
    print "executing: $cmd\n";
    my $file_handle = system($cmd);
    my $exit_status = $? >> 8;
    print "\texit status: $exit_status handle: $file_handle\n";
	
	return $exit_status;
}
