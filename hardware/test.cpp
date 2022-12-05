#include <xtensor-fftw/basic.hpp>  // rfft, irfft
#include <xtensor-fftw/helper.hpp> // rfftscale
#include <xtensor/xarray.hpp>
#include <xtensor/xbuilder.hpp> // xt::arange
#include <xtensor/xmath.hpp>    // xt::sin, cos
#include <complex>
#include <xtensor/xio.hpp>

#include <iostream>

int main(int argc, char const *argv[])
{
    // generate a sinusoid field
    double dx = M_PI / 100;
    xt::xarray<double> x = xt::arange(0., 2 * M_PI, dx);
    xt::xarray<double> sinus = xt::sin(x);

    // transform to Fourier space
    auto sin_fs = xt::fftw::rfft(sinus);

    // // multiply by i*k
    // std::complex<double> i{0, 1};
    // auto k = xt::fftw::rfftscale<double>(sinus.shape()[0], dx);
    // xt::xarray<std::complex<double>> sin_derivative_fs = xt::eval(i * k * sin_fs);

    // // transform back to normal space
    // auto sin_derivative = xt::fftw::irfft(sin_derivative_fs);

    // std::cout << "x:              " << x << std::endl;
    // std::cout << "sin:            " << sin << std::endl;
    // std::cout << "cos:            " << xt::cos(x) << std::endl;
    // std::cout << "sin_derivative: " << sin_derivative << std::endl;
    
    return 0;
}
