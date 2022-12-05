#pragma once

#include "Generator.hpp"
#include "Oscilloscope.hpp"

#include <vector>
#include <iomanip>

#include <xtensor/xarray.hpp>
#include <xtensor/xcsv.hpp>
#include <xtensor/xsort.hpp>

class Experiment
{
public:
    Experiment()
    {
        std::cout << osc.query("*IDN?") << std::endl;
        std::cout << osc.query("*IDN?") << std::endl;
        std::cout << osc.query("*IDN?") << std::endl;
    }

    void preparing()
    {
        double start_freq = 1590;
        double start_ampl = 10.0;

        gen.set_frequency(start_freq);
        gen.set_amplitude(start_ampl);

        osc.auto_setup();
        usleep(5e6);
    }

    auto resonance_curve()
    {
        std::cerr << "Start experiment..." << std::endl;

        std::vector<double> freq;
        std::vector<double> ampl;

        std::cout << "Freq,\tAmpl" << std::endl;

        for (size_t f = 1400; f < 1800; f += 5)
        {
            gen.set_frequency(f);
            double fr = 0;
            double am = 0;

            usleep(0.1e6);

            try
            {
                fr = osc.get_parameter_value("FREQ", "Hz");
                am = osc.get_parameter_value("PKPK", "V");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }

            if (am * fr) {
                freq.push_back(fr);
                ampl.push_back(am);
            }
        }

        std::cerr << "End experiment!" << std::endl;
        

        return std::make_pair(freq, ampl);
    }

private:
    Generator gen;
    Oscilloscope osc;
};
