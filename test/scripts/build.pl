use File::Basename;
use feature "switch";
use lib 'test/scripts';
use Jobs;

# read command line params
my $jobname = shift;

# get script directory
my $scriptdir = File::Basename::dirname($0);

# read ini file
my $inifile = $scriptdir . "/jobs.ini";
my %job = Jobs::get($inifile, $jobname);

# examine the platform
given ($job{'Platform'}) {
	when ("Win7") {
		# construct a build command	
		my @cmd;
		if ($job{'ToolChain'} eq "mingw") {
			@cmd = ($scriptdir . "\\build_win_mingw.bat", $job{'QtDir'}, $job{'Config'}, $job{'MinGWDir'});
		}
		if ($job{'ToolChain'} eq "vs2005") {
			@cmd = ($scriptdir . "\\build_win_vs2005.bat", $job{'QtDir'}, $job{'Config'});
		}
		if ($job{'ToolChain'} eq "vs2008") {
			@cmd = ($scriptdir . "\\build_win_vs2008.bat", $job{'QtDir'}, $job{'Config'});
		}
		if ($job{'ToolChain'} eq "vs2010") {
			@cmd = ($scriptdir . "\\build_win_vs2010.bat", $job{'QtDir'}, $job{'Config'});
		}
		# run the build command
		system (@cmd) == 0 or die "system @cmd failed: $?";
	}
	default {
		die "Unknown platform " . $job{'Platform'};
	}
}