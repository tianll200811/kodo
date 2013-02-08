// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef KODO_CONTINIOUS_ID_ITERATOR_HPP
#define KODO_CONTINIOUS_ID_ITERATOR_HPP


namespace kodo
{

    ///
    template<class Field>
    class continious_symbol_id
    {
    public:

        typedef typename Field::value_type value_type;

        struct iterator;

        continious_symbol_id(uint8_t *data);

        /// @return the
        uint8_t* data() const;

        ///
        void set(uint32_t index, value_type value)
            {
            }

        std::vector<uint8_t> m_data;
    };

    template<class SuperCoder>
    class symbol_id_math : public SuperCoder
    {
    public:

        typedef typename SuperCoder::symbol_id symbol_id;

    public:
        void multiply(symbol_id &id, value_type coefficient)
            {
                SuperCoder::multiply(
                    id.data(), coefficient, id.length());
            }
    };


    template<class SuperCoder>
    class symbol_math : public SuperCoder
    {
        template<class SymbolType>
        void multiply(SymbolType &symbol, value_type coefficient)
            {
                SuperCoder::multiply(
                    symbol.data(), coefficient, symbol.length());
            }
    };


    template<class SuperCoder>
    class continious_id_iterator : public SuperCoder
    {
    public:

        /// The field type
        typedef typename SuperCoder::field_type field_type;

        /// The value type
        typedef typename field_type::value_type value_type;

    public:


        struct id_iterator
        {
            id_iterator(uint8_t *symbol_id)
        };

        


/// The factory layer associated with this coder.
        /// Maintains the block generator needed for the encoding
        /// vectors.
        class factory : public SuperCoder::factory
        {
        public:

            /// @copydoc final_coder_factory::factory::factory()
            factory(uint32_t max_symbols, uint32_t max_symbol_size)
                : SuperCoder::factory(max_symbols, max_symbol_size)
                { }

            /// @copydoc final_coder_factory::factory::build()
            pointer build(uint32_t symbols, uint32_t symbol_size)
                {
                    pointer coder =
                        SuperCoder::factory::build(symbols, symbol_size);

                    uint32_t vector_length = vector_type::length( symbols );

                    typename generator_block::pointer block =
                        m_generator_factory.build( vector_length );

                    coder->m_generator = block;

                    return coder;
                }

            /// Set the see used by the generator block
            void set_seed(uint32_t seed)
                {
                    m_generator_factory.set_seed(seed);
                }

        private:

            typename generator_block::factory m_generator_factory;
        };


    public:

        /// Generates the coefficients for a linear block vector into the
        /// requested buffer
        void generate(uint32_t index, value_type *vector_buffer)
            {
                assert(vector_buffer != 0);

                // Fill the encoding vector
                assert(m_generator);

                m_generator->fill(index, vector_buffer);
            }

    protected:

        /// The linear block vector generator
        typename generator_block::pointer m_generator;
    };
}

#endif
