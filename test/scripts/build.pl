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
	
		$scriptdir =~ s/\//\\/g; # replace / -> \
		
		# construct a build command	
		if ($job{'ToolChain'} eq "mingw") {
			run($scriptdir . "\\build_win_mingw.bat", $job{'QtDir'}, $job{'Config'}, $job{'MinGWDir'});
		}
		elsif ($job{'ToolChain'} eq "vs2005") {
			run($scriptdir . "\\build_win_vs2005.bat", $job{'QtDir'}, $job{'Config'});
		}
		elsif ($job{'ToolChain'} eq "vs2008") {
			run($scriptdir . "\\build_win_vs2008.bat", $job{'QtDir'}, $job{'Config'});
		}
		elsif ($job{'ToolChain'} eq "vs2010") {
			run($scriptdir . "\\build_win_vs2010.bat", $job{'QtDir'}, $job{'Config'});
		}
		else {
			die "Unknown toolchain!";
		}
	}
	
	when ("Mac") {
		
		# setup build environment
		$ENV{'QTDIR'} = $job{'QtDir'};
		$ENV{'PATH'} = $job{'QtDir'} . "/bin:" . $ENV{'PATH'};
		
		# run qmake
		my $cmd;
		if ($job{'ToolChain'} eq "clang") {
			run("qmake -r -spec unsupported/macx-clang CONFIG+=" . $job{'Config'});
		}
		elsif ($job{'ToolChain'} eq "gcc") {
			run("qmake -r CONFIG+=" . $job{'Config'});
		}
		else {
			die "Unknown toolchain!";
		}
		
		# run make
		run("make");
	}
	
	when ("Linux") {
		
		# setup build environment
		$ENV{'QTDIR'} = $job{'QtDir'};
		$ENV{'PATH'} = $job{'QtDir'} . "/bin:" . $ENV{'PATH'};
		
		# run qmake
		my $cmd;
		if ($job{'ToolChain'} eq "gcc") {
			run("qmake -r CONFIG+=" . $job{'Config'});
		}
		else {
			die "Unknown toolchain!";
		}
		
		# run make
		run("make");
	}
	
	default {
		die "Unknown platform " . $job{'Platform'};
	}
}

sub run {
	my $cmd;
	foreach (@_) {
		$cmd .= "$_ ";
	}
	print "running : $cmd\n";
	system(@_) == 0 or die "system \"$cmd\" failed: $?";
}