package Jobs;
use File::Basename;
use IniFiles;

sub get {
	my $inifile = shift;
	my $jobname = shift;

    # Strip the prefix from job name when using ${bamboo.buildPlanName}
	my $prefix = "Digia Qt Commercial - Chart component - ";
	$jobname =~ s/$prefix//;

	# read ini file
	my %cfg;
	tie %cfg, 'Config::IniFiles', ( -file => $inifile );

	# get section from ini by jobname
	my %job = %{$cfg{$jobname}};
	if (!%job) {
		die ("Unknown jobname! Check $inifile and bamboo job name.");
	}

	# print out the ini settings
	print "\n\nini file: $inifile\n";
	print "[$jobname]\n";
	foreach (keys %job) {
		print $_ . "=" . $job{$_} . "\n";
	}
	print "\n";
	
	return %job;
}

1;