// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef KODO_RECODING_SYMBOL_ID_HPP
#define KODO_RECODING_SYMBOL_ID_HPP

#include <cstdint>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <fifi/fifi_utils.hpp>

namespace kodo
{

    /// @brief Randomly recombines existing coding coefficients to
    ///        allow a decoder to produce recoded packets.
    ///
    /// @ingroup symbol_id_layers
    /// @ingroup factory_layers
    template<class SuperCoder>
    class recoding_symbol_id : public SuperCoder
    {
    public:

        /// The random generator used
        typedef boost::random::mt19937 generator_type;

        /// The type generated by this random generator
        typedef generator_type::result_type result_type;

        /// The value type
        typedef typename SuperCoder::value_type value_type;

        /// The finite field type
        typedef typename SuperCoder::field_type field_type;

    public:

        /// @ingroup factory_layers
        /// The factory layer associated with this coder.
        class factory : public SuperCoder::factory
        {
        public:

            /// @copydoc layer::factory::factory()
            factory(uint32_t max_symbols, uint32_t max_symbol_size)
                : SuperCoder::factory(max_symbols, max_symbol_size)
                { }

            /// @copydoc layer::factory::max_id_size()
            uint32_t max_id_size() const
                {
                    return SuperCoder::max_coefficients_size();
                }
        };

    public:

        /// @copydoc layer::initialize()
        void initialize(uint32_t symbols, uint32_t symbol_size)
            {
                SuperCoder::initialize(symbols, symbol_size);

                m_id_size = fifi::bytes_needed<field_type>(symbols);
                assert(m_id_size > 0);
            }

        /// Will write the recoded encoding vector (symbol id) into the
        /// symbol_id buffer. The coding coefficients used to produce the
        /// recoded encoding vector will be available in the
        /// symbol_coefficient buffer.
        ///
        /// @copydoc layer::write_id()
        uint32_t write_id(uint8_t *symbol_id, uint8_t **symbol_coefficients)
            {
                assert(symbol_id != 0);
                assert(symbol_coefficients != 0);

                for(uint32_t i = 0; i < m_id_size; ++i)
                {
                    symbol_id[i] = m_distribution(m_random_generator);
                }

                *symbol_coefficients = symbol_id;

                return m_id_size;
            }


        /// @copydoc layer::id_size()
        uint32_t id_size() const
            {
                return m_id_size;
            }

    protected:

        /// Seeds the random generator used
        /// @param seed The seed used for the random generator
        void seed(result_type seed)
            {
                return m_random_generator.seed(seed);
            }

    private:

        /// Initialize the coefficient storage
        void Initialize_storage(uint32_t max_coefficients_size)
            {
                assert(max_coefficients_size > 0);

                // Note, that resize will not re-allocate anything
                // as long as the sizes are not larger than
                // previously. So this call should only have an
                // effect the first time this function is called.
                m_coefficients_storage.resize(max_coefficients_size);
            }

    protected:

        /// The distribution wrapping the random generator
        boost::random::uniform_int_distribution<uint8_t> m_distribution;

        /// The random generator
        generator_type m_random_generator;

        /// The number of bytes needed to store the symbol id
        /// coding coefficients
        uint32_t m_id_size;

        /// Buffer for the recoding coefficients
        std::vector<uint8_t> m_coefficients;
    };

}

#endif

