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

# Windows specific magic
if ($job{'Platform'} eq "Win7") {
	$ENV{'PATH'} .= ";" . $job{'QtDir'} . "\\bin"; # Add qtdir to path
}

# Go through all the files in the test folder
my $root_path = abs_path();
my $test_path = "$root_path/bin/test/";
opendir (TESTAPPDIR, "$test_path") or die "Couldn't open test app dir";
@files = <TESTAPPDIR>;
while ($testapp = readdir TESTAPPDIR) {
    # autotest is an executable beginning with "tst_"
    if (index($testapp, "tst_") == 0) {
        if (-x "$test_path$testapp") {
            my $cmd_postfix = "";
            if ($^O eq "darwin") {
                # On OSX the actual test binary is in a sub folder
                $cmd_postfix = "/Contents/MacOS/$testapp";
                $cmd_postfix = substr($cmd_postfix, 0, rindex($cmd_postfix, ".app"));
            }
            # Generate path for test results
            my $test_result_path = "test-reports/$testapp.xml";
            mkdir dirname($test_result_path);
            # Execute the actual auto test
            executeTestApp("$test_path$testapp$cmd_postfix", "-xunitxml -o $test_result_path");
        } else {
            #print "file $testapp not executable\n";
        }
    }
}
closedir TESTAPPDIR;

sub executeTestApp($) {
    my $test_app_path = $_[0];
    my $parameters = $_[1];

    print "executing: $cmd_prefix$test_app_path $parameters\n";
    my $file_handle = system("$test_app_path $parameters");

    my $exit_status = $? >> 8;
#    print "exit: $exit_status \n";
#    print "handle: $file_handle\n";
}
