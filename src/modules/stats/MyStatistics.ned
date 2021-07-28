package sdvn.modules.stats;


simple MyStatistics {
	
	parameters:
	    
	    @class(MyStatistics);
	    @display("i=block/table2");
	    
	    @signal[roi](type=long);
	    @statistic[roi](record=last;description="number of vehicles in ROI");
	    
	    @signal[receivedAlerts](type=long);
	    @statistic[receivedAlerts](record=count;description="number of vehicles that recived alert successfuly");
	    
	    @statistic[informationCoverage](source=count(receivedAlerts)/last(roi); record=last); 
	    
	    @signal[delay](type=double);
	    @statistic[delay](record=stats,vector); 
	    
	    @statistic[averageServiceDelay](source=sum(delay)/last(roi); record=last);
	    
	    @signal[duplicatedMessages](type=long);
    	@statistic[duplicatedMessages](record=count); 
    
    	@signal[rebroadcast](type=long);
    	@statistic[rebroadcast](record=count);    
}