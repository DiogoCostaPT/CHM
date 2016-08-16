#include "interpolation.h"

interpolation::interpolation(interp_alg ia, size_t size)
{
    init(ia,size);
}

void interpolation::init(interp_alg ia, size_t size)
{

    if (ia == interp_alg::tpspline)
    {
        if (size)
            base = boost::make_shared<thin_plate_spline>(size);
        else
            base = boost::make_shared<thin_plate_spline>();
    }
    else if(ia == interp_alg::idw)
    {
        base = boost::make_shared<inv_dist>();
    }
    else
    {
        BOOST_THROW_EXCEPTION(interp_unknown_type() << errstr_info("Unknown interpolation type"));
    }


    this->size = size;
    this->ia = ia;
}

interpolation::interpolation()
{
    base = nullptr;
}
interpolation::~interpolation()
{

}

double interpolation::operator()(std::vector< boost::tuple<double,double,double> >& sample_points, boost::tuple<double,double,double>& query_point)
{
    if (sample_points.size() == 0)
    {
        BOOST_THROW_EXCEPTION(config_error() << errstr_info("Interpolation sample point length = 0."));
    }

    if(sample_points.size() != this->size || this->size == 0)
    {

        this->init(ia,sample_points.size());
    }

    return base->operator()(sample_points,query_point);
}
