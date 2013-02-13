// Copyright Steinwurf ApS 2011-2012.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#ifndef KODO_PAYLOAD_ENCODER_HPP
#define KODO_PAYLOAD_ENCODER_HPP

#include <cstdint>

namespace kodo
{

    /// @ingroup payload_codec_layers
    /// @ingroup factory_layers
    /// The payload encoder splits payload buffer into symbol_id and symbol
    /// buffers.
    template<class SuperCoder>
    class payload_encoder : public SuperCoder
    {
    public:

        /// The factory layer associated with this coder.
        /// In this case only needed to provide the max_payload_size()
        /// function.
        class factory : public SuperCoder::factory
        {
        public:

            /// @copydoc layer::factory::factory()
            factory(uint32_t max_symbols, uint32_t max_symbol_size)
                : SuperCoder::factory(max_symbols, max_symbol_size)
                { }

            /// @copydoc layer::factory::max_payload_size()
            uint32_t max_payload_size() const
                {
                    return SuperCoder::factory::max_symbol_size() +
                        SuperCoder::factory::max_header_size();
                }
        };

    public:

        /// Encodes a symbol to the provided buffer using the following
        /// layout:
        ///
        /// @code
        ///   +-------------------+---------------+
        ///   |    symbol data    |   symbol id   |
        ///   +-------------------+---------------+
        /// @endcode
        ///
        /// The reason the symbol data is placed first in the payload
        /// buffer is to enable 16 byte-alignment of the symbol data.
        /// If the variable length id would be place in front of the
        /// symbol it would easily become unaligned. Unaligned symbol
        /// data access will most likely result in very bad performance.
        /// @copydoc layer::encode(uint8_t*)
        uint32_t encode(uint8_t *payload)
            {
                assert(payload != 0);

                uint8_t *symbol_data = payload;
                uint8_t *symbol_id = payload + SuperCoder::symbol_size();

                // The non-payload layers only return the number of bytes
                // use for the symbol_id here we return _all_ the bytes used.
                return SuperCoder::encode(symbol_data, symbol_id)
                    + SuperCoder::symbol_size();
            }

        /// @copydoc layer::payload_size()
        uint32_t payload_size() const
            {
                return SuperCoder::symbol_size() +
                    SuperCoder::header_size();
            }
    };
}

#endif

