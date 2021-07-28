package sdvn.simulations.stop;

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

import sdvn.modules.stats.MyStatistics;

network StopScenario extends Scenario
{
    submodules:

        stats: MyStatistics {
            @display("p=260,119");
        }
}
