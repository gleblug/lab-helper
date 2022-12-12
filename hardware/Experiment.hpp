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
    Experiment(Generator &generator, Oscilloscope &oscilloscope) :
        gen(generator),
        osc(oscilloscope)
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

    auto frequency_response(double fmin, double fmax, double step)
    {
        std::cerr << "Start experiment..." << std::endl;

        std::vector<double> freq;
        std::vector<double> ampl;

        osc.set_vdiv(10);

        std::cerr << fmin << " " << fmax << " " << step << std::endl;

        for (double f = fmin; f < fmax; f += step)
        {
            gen.set_frequency(f);
            double fr = 0;
            double am = 0;

            usleep(0.5e6);

            try
            {
                bool goodMeasurement = false;

                while (!goodMeasurement)
                {
                    am = osc.get_parameter_value("AMPL", "V");
                    double vdiv = osc.get_vdiv();

                    std::cout << vdiv << std::endl;

                    if (am < vdiv * 2)
                        osc.set_vdiv(am / 4.0f);
                    else if (am > vdiv * 6)
                        osc.set_vdiv(am / 4.0f);
                    else
                        goodMeasurement = true;
                }
                fr = f;
//                fr = osc.get_parameter_value("FREQ", "Hz");

                std::cout << "Measure" << std::endl;
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
