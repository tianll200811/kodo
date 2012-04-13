// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <gtest/gtest.h>

#include <stdint.h>

#include <kodo/rs/vandermonde_matrix.h>

#include <boost/make_shared.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

// Test function for printing the matrix
template<class Field>
void print_matrix(const kodo::vandermonde_matrix<Field> &matrix)
{
    for(uint32_t i = 0; i < Field::order - 1; ++i)
        {
            const typename Field::value_type *v = matrix.coefficients(i);

            std::cout << "COL " << i << ": ";

            for(uint32_t j = 0; j < matrix.symbols(); ++j)
            {
                std::cout << (uint32_t)v[j] << " ";
            }
            std::cout << std::endl;
        }
}

TEST(TestVandermondeMatrix, test_construct)
{
    // The uniform int distribution
    typedef boost::random::uniform_int_distribution<uint32_t>
            uniform_int;

    // The random generator
    boost::random::mt19937 random_generator;
    random_generator.seed(static_cast<uint32_t>(time(0)));

    {
        typedef fifi::binary8 field_type;

        uniform_int choose_symbols
            = uniform_int(1, field_type::order - 1);

        uint32_t symbols = choose_symbols(random_generator);

        typedef fifi::full_table<field_type> field_impl;
        boost::shared_ptr<field_impl> field = boost::make_shared<field_impl>();

        kodo::vandermonde_matrix<fifi::binary8> matrix(false, symbols, field);

    }
}

extern const uint32_t test_values[];

TEST(TestVandermondeMatrix, test_matrix_values)
{

    {
        typedef fifi::binary8 field_type;

        uint32_t symbols = 10;

        typedef fifi::full_table<field_type> field_impl;
        boost::shared_ptr<field_impl> field = boost::make_shared<field_impl>();

        kodo::vandermonde_matrix<fifi::binary8> matrix(false, symbols, field);


        for(uint32_t i = 0; i < field_type::order - 1; ++i)
        {
            const field_type::value_type *v = matrix.coefficients(i);

            for(uint32_t j = 0; j < symbols; ++j)
            {
                uint32_t expected = test_values[i * symbols + j];
                uint32_t actual = v[j];

                EXPECT_EQ(expected, actual);
            }
        }

    }
}


// Values generated using Matlab using the following script:
//
//  m = 8
//  n = 2^m - 1
//  k = 10
//
//  i_max = k-1
//  j_max = n-1
//
//  l = zeros(j_max, i_max)
//  for j = 0:j_max
//    for i = 0:i_max
//      xgf = gf(2,m)^(i*j);
//      l(j+1, i+1) = double(xgf.x);
//    end
//    str = sprintf('row %d', j);
//    disp(str)
//  end
//
const uint32_t test_values[] = {1,1,1,1,1,1,1,1,1,1,1,2,4,8,16,32,64,128,29,58,1,4,16,64,29,116,205,19,76,45,1,8,64,58,205,38,45,117,143,12,1,16,29,205,76,180,143,24,157,37,1,32,116,38,180,3,96,156,106,193,1,64,205,45,143,96,37,181,70,80,1,128,19,117,24,156,181,140,93,161,1,29,76,143,157,106,70,93,95,101,1,58,45,12,37,193,80,161,101,231,1,116,180,96,106,5,185,94,253,223,1,232,234,39,238,160,97,60,254,134,1,205,143,37,70,185,101,107,217,208,1,135,6,53,20,190,120,163,13,237,1,19,24,181,93,94,107,67,129,102,1,38,96,193,185,15,223,26,59,169,1,76,157,70,95,253,217,129,133,168,1,152,78,10,153,214,68,147,79,146,1,45,37,80,101,223,208,102,168,191,1,90,148,186,30,226,62,109,73,179,1,180,106,185,253,17,59,132,230,150,1,117,181,161,107,26,102,41,252,87,1,234,238,97,254,103,184,57,227,7,1,201,159,47,91,124,33,209,149,166,1,143,70,101,217,59,168,252,130,195,1,3,5,15,17,51,85,255,28,36,1,6,20,120,13,46,228,98,81,251,1,12,80,231,208,169,191,87,195,125,1,24,93,107,129,132,252,200,18,173,1,48,105,127,248,77,241,224,247,64,1,96,185,223,59,85,150,89,44,38,1,192,222,182,151,114,110,155,27,143,1,157,95,217,133,230,130,18,2,39,1,39,97,134,184,145,7,245,58,181,1,78,153,68,79,215,221,11,152,10,1,156,94,26,132,255,89,233,3,185,1,37,101,208,168,150,195,173,39,47,1,74,137,206,82,55,138,16,212,120,1,148,30,62,73,174,61,232,140,127,1,53,120,237,228,100,251,45,186,217,1,106,253,59,230,28,44,3,190,26,1,212,211,197,198,167,207,157,202,62,1,181,107,102,252,89,173,53,231,197,1,119,177,23,123,239,8,159,225,184,1,238,254,184,227,172,58,40,175,21,1,193,223,169,150,36,38,185,26,85,1,159,91,33,149,244,117,194,31,115,1,35,113,21,165,235,12,137,118,252,1,70,217,168,130,44,39,231,23,219,1,140,67,41,200,233,53,254,158,110,1,5,17,85,28,108,193,226,77,100,1,10,68,146,221,1,10,68,146,221,1,20,13,228,81,32,186,189,209,242,1,40,52,115,121,116,161,248,229,138,1,80,208,191,195,38,47,197,219,245,1,160,103,145,172,180,15,46,55,44,1,93,129,252,18,3,231,158,25,54,1,186,62,179,61,96,127,168,56,8,1,105,248,241,247,156,182,170,162,205,1,210,199,219,203,106,134,183,155,117,1,185,59,150,44,193,26,145,36,96,1,111,236,196,250,5,206,123,243,53,1,222,151,110,27,160,237,75,88,70,1,161,102,87,173,185,197,110,54,186,1,95,133,130,2,190,23,25,4,97,1,190,46,100,32,94,169,28,116,15,1,97,184,7,58,15,21,166,45,107,1,194,218,56,135,253,41,249,6,182,1,153,79,221,152,214,146,69,78,68,1,47,33,166,117,223,115,61,181,206,1,94,132,89,3,226,145,235,5,59,1,188,42,242,48,17,179,176,105,23,1,101,168,195,39,26,219,54,97,33,1,202,154,86,74,103,196,2,137,41,1,137,82,138,212,124,87,29,211,228,1,15,85,36,193,59,100,38,223,145,1,30,73,61,140,51,56,234,67,241,1,60,57,245,40,46,166,48,52,196,1,120,228,251,186,169,242,37,62,130,1,240,183,139,111,132,86,119,236,56,1,253,230,44,190,77,36,5,46,89,1,231,191,125,47,85,245,186,33,86,1,211,198,207,202,114,139,95,154,61,1,187,63,54,60,230,125,188,57,139,1,107,252,173,231,145,54,120,191,207,1,214,215,1,214,215,1,214,215,1,1,177,123,8,225,255,64,91,171,58,1,127,241,64,182,150,205,134,110,45,1,254,227,58,175,55,45,52,50,12,1,225,171,205,34,174,143,31,112,37,1,223,150,38,26,100,96,59,89,193,1,163,98,45,189,28,37,204,43,80,1,91,149,117,31,167,181,218,72,161,1,182,110,143,237,89,70,21,251,101,1,113,165,12,118,239,80,82,176,231,1,226,174,96,51,172,185,114,108,223,1,217,130,39,23,36,97,191,8,134,1,175,50,37,109,244,101,229,232,208,1,67,200,53,158,235,120,227,90,237,1,134,7,181,21,44,107,196,12,102,1,17,28,193,77,233,223,174,156,169,1,34,112,70,164,108,217,141,119,168,1,68,221,10,146,1,68,221,10,146,1,136,83,80,213,32,208,178,210,191,1,13,81,186,209,116,62,43,194,179,1,26,89,185,145,38,59,36,15,150,1,52,121,161,229,180,102,247,187,87,1,104,249,97,246,3,184,22,163,7,1,208,195,47,219,96,33,207,134,166,1,189,43,101,49,156,168,71,104,195,1,103,172,15,55,106,85,32,124,36,1,206,138,120,87,193,228,205,197,251,1,129,18,231,25,5,191,90,92,125,1,31,72,107,141,160,252,6,66,173,1,62,61,127,56,185,241,39,41,64,1,124,244,223,167,190,150,106,114,38,1,248,247,182,162,94,110,35,99,143,1,237,251,217,242,15,130,80,179,39,1,199,203,134,155,253,7,111,75,181,1,147,11,68,69,214,221,153,220,10,1,59,44,26,36,223,89,15,100,185,1,118,176,208,122,226,195,211,224,47,1,236,250,206,243,17,138,225,178,120,1,197,207,62,139,26,61,217,86,127,1,151,27,237,88,103,251,136,144,217,1,51,108,59,233,124,44,103,235,26,1,102,173,197,54,59,207,237,125,62,1,204,142,102,71,51,173,151,216,197,1,133,2,23,4,46,8,92,16,184,1,23,8,184,64,169,58,33,205,21,1,46,32,169,116,132,38,77,180,85,1,92,128,33,19,77,117,73,24,115,1,184,58,21,45,85,12,115,37,252,1,109,232,168,234,114,39,63,238,219,1,218,135,41,6,230,53,246,20,110,1,169,38,85,96,145,193,150,185,100,1,79,152,146,78,215,10,220,153,221,1,158,90,228,148,255,186,50,30,242,1,33,117,115,181,150,161,56,107,138,1,66,201,191,159,55,47,81,91,245,1,132,3,145,5,174,15,239,17,44,1,21,12,252,80,100,231,138,208,54,1,42,48,179,105,28,127,122,248,8,1,84,192,241,222,167,182,203,151,205,1,168,39,219,97,89,134,125,184,117,1,77,156,150,94,239,26,108,132,96,1,154,74,196,137,172,206,4,82,53,1,41,53,110,120,36,237,58,228,70,1,82,212,87,211,244,197,76,198,186,1,164,119,130,177,235,23,201,123,97,1,85,193,100,223,44,169,96,150,15,1,170,35,7,113,233,21,74,165,107,1,73,140,56,67,108,41,238,200,182,1,146,10,221,68,1,146,10,221,68,1,57,40,166,52,32,115,105,121,206,1,114,160,89,103,116,145,190,172,59,1,228,186,242,62,38,179,101,61,23,1,213,210,195,199,180,219,240,203,33,1,183,111,86,236,3,196,177,250,41,1,115,161,138,102,96,87,182,173,228,1,230,190,36,46,156,100,17,32,145,1,209,194,61,218,106,56,104,135,241,1,191,47,245,33,193,166,62,117,196,1,99,188,251,42,5,242,118,48,130,1,198,202,139,154,160,86,133,74,56,1,145,15,44,85,185,36,169,193,89,1,63,60,125,57,190,245,42,40,86,1,126,240,207,183,94,139,164,111,61,1,252,231,54,191,15,125,228,47,139,1,229,187,173,63,253,54,99,60,207,1,215,214,1,215,214,1,215,214,1,1,179,127,8,241,223,64,219,182,58,1,123,225,64,171,226,205,149,34,45,1,246,163,58,98,17,45,65,189,12,1,241,182,205,110,26,143,7,237,37,1,255,226,38,174,103,96,167,51,193,1,227,175,45,50,124,37,121,109,80,1,219,134,117,7,59,181,86,21,161,1,171,34,143,112,51,70,72,164,101,1,75,136,12,83,46,80,243,213,231,1,150,26,96,89,169,185,44,145,223,1,49,104,39,249,132,97,131,246,134,1,98,189,37,43,77,101,142,49,208,1,196,206,53,138,85,120,64,87,237,1,149,31,181,72,114,107,135,141,102,1,55,124,193,244,230,223,180,167,169,1,110,237,70,251,145,217,12,242,168,1,220,147,10,11,215,68,78,69,146,1,165,118,80,176,255,208,212,122,191,1,87,197,186,207,150,62,70,139,179,1,174,51,185,108,55,59,160,233,150,1,65,204,161,142,174,102,222,71,87,1,130,23,97,8,100,184,47,64,7,1,25,92,47,128,28,33,30,19,166,1,50,109,101,232,167,168,187,234,195,1,100,169,15,38,89,85,223,96,36,1,200,158,120,90,239,228,175,148,251,1,141,66,231,201,172,191,13,159,125,1,7,21,107,12,36,252,206,80,173,1,14,84,127,192,244,241,199,222,64,1,28,77,223,156,235,150,51,94,38,1,56,41,182,53,44,110,184,120,143,1,112,164,217,119,233,130,66,177,39,1,224,170,134,35,108,7,154,113,181,1,221,146,68,10,1,221,146,68,10,1,167,114,26,160,32,89,230,103,185,1,83,213,208,210,116,195,126,199,47,1,166,115,206,161,38,138,241,102,120,1,81,209,62,194,180,61,49,218,127,1,162,99,237,188,3,251,165,42,217,1,89,145,59,15,96,44,100,85,26,1,178,126,197,240,156,207,112,183,62,1,121,229,102,187,106,173,162,63,197,1,242,179,23,127,193,8,195,241,184,1,249,246,184,163,5,58,9,98,21,1,239,255,169,226,160,38,244,174,85,1,195,219,33,134,185,117,139,7,115,1,155,75,21,136,190,12,250,83,252,1,43,49,168,104,94,39,216,249,219,1,86,196,41,206,15,53,8,138,110,1,172,55,85,124,253,193,116,244,100,1,69,220,146,147,214,10,152,11,221,1,138,87,228,197,223,186,143,207,242,1,9,65,115,204,226,161,192,142,138,1,18,25,191,92,17,47,148,128,245,1,36,100,145,169,26,15,193,38,44,1,72,141,252,66,103,231,20,201,54,1,144,14,179,84,124,127,210,192,8,1,61,56,241,41,59,182,97,53,205,1,122,224,219,170,51,134,202,35,117,1,244,167,150,114,46,26,253,160,96,1,245,166,196,115,169,206,127,161,53,1,247,162,110,99,132,237,113,188,70,1,243,178,87,126,77,197,34,240,186,1,251,242,130,179,85,23,208,127,97,1,235,239,100,255,114,169,124,226,15,1,203,155,7,75,230,21,236,136,107,1,139,86,56,196,145,41,23,206,182,1,11,69,221,220,215,146,79,147,68,1,22,9,166,65,255,115,84,204,206,1,44,36,89,100,150,145,85,169,59,1,88,144,242,14,55,179,213,84,23,1,176,122,195,224,174,219,198,170,33,1,125,245,86,166,100,196,179,115,41,1,250,243,138,178,28,87,171,126,228,1,233,235,36,239,167,100,55,255,145,1,207,139,61,86,89,56,130,196,241,1,131,22,245,9,239,166,14,65,196,1,27,88,251,144,172,242,83,14,130,1,54,125,139,245,36,86,242,166,56,1,108,233,44,235,244,36,172,239,89,1,216,131,125,22,235,245,144,9,86,1,173,54,207,125,44,139,251,245,61,1,71,216,54,131,233,125,88,22,139,1,142,71,173,216,108,54,27,131,207};