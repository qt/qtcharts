use lib 'test/scripts'; # for IniFiles
use File::Basename;
use IniFiles;
use feature "switch";

# read command line params
my $jobname = shift;

# Strip the prefix from job name when using ${bamboo.buildPlanName}
my $prefix = "Digia Qt Commercial - Chart component - ";
$jobname =~ s/$prefix//;

# read ini file
my $scriptdir = File::Basename::dirname($0);
my $inifile = $scriptdir . "/jobs.ini";
my %cfg;
tie %cfg, 'Config::IniFiles', ( -file => $inifile );

# get section from ini by jobname
my %build = %{$cfg{$jobname}};
if (!%build) {
	die ("Unknown jobname! Check $inifile and bamboo job name.");
}

# print out the ini settings
print "\n\n$jobname\n";
print "**********\n";
foreach (keys %build) {
	print $_ . " : " . $build{$_} . "\n";
}

# examine the platform
given ($build{'Platform'}) {
	when ("Win7") {
		# construct a build command	
		my @cmd;
		if ($build{'ToolChain'} eq "mingw") {
			@cmd = ($scriptdir . "\\build_win_mingw.bat", $build{'QtDir'}, $build{'Config'}, $build{'MinGWDir'});
		}
		if ($build{'ToolChain'} eq "vs2005") {
			@cmd = ($scriptdir . "\\build_win_vs2005.bat", $build{'QtDir'}, $build{'Config'});
		}
		if ($build{'ToolChain'} eq "vs2008") {
			@cmd = ($scriptdir . "\\build_win_vs2008.bat", $build{'QtDir'}, $build{'Config'});
		}
		if ($build{'ToolChain'} eq "vs2010") {
			@cmd = ($scriptdir . "\\build_win_vs2010.bat", $build{'QtDir'}, $build{'Config'});
		}
		# run the build command
		system (@cmd) == 0 or die "system @cmd failed: $?";
	}
	default {
		die "Unknown platform " . $build{'Platform'};
	}
}