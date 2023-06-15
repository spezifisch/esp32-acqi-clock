#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/hal.h"

namespace esphome
{
    namespace tm1640
    {

        class TM1640Display;

        using tm1640_writer_t = std::function<void(TM1640Display &)>;

        class TM1640Display : public PollingComponent
        {
        public:
            void set_writer(tm1640_writer_t &&writer) { this->writer_ = writer; }

            void setup() override;

            void dump_config() override;

            void set_clk_pin(GPIOPin *pin) { clk_pin_ = pin; }
            void set_dio_pin(GPIOPin *pin) { dio_pin_ = pin; }

            float get_setup_priority() const override;

            void update() override;

            /// Evaluate the printf-format and print the result at the given position.
            uint8_t printf(uint8_t pos, const char *format, ...) __attribute__((format(printf, 3, 4)));
            /// Evaluate the printf-format and print the result at position 0.
            uint8_t printf(const char *format, ...) __attribute__((format(printf, 2, 3)));

            /// Print `str` at the given position.
            uint8_t print(uint8_t pos, const char *str);
            /// Print `str` at position 0.
            uint8_t print(const char *str);

            // intensity values: 0-7
            void set_intensity(uint8_t intensity) { this->intensity_ = intensity; }
            // length: always set to 11 for gtclock
            void set_length(uint8_t length) { this->length_ = length; }

            void display();

            // gtclock-specific display symbols
            struct Flags
            {
                bool pm;
                bool alarm1;
                bool alarm2;
                bool colon_hi; // upper dot of : (between hours and minutes)
                bool colon_lo; // lower dot
                bool colon; // both dots of : (_hi/_lo and this one are or'ed)
                bool snooze; // zZ
                bool month10_hi; // upper part of the 1 in the 10th place of month number
                bool month10_lo; // lower part of the 1
                bool month; // M
                bool day; // D
                bool date_dash; // between month and day
                bool degree;
            };
            Flags flags;
            void clear_flags();

        protected:
            void bit_delay_();
            void send_byte_(uint8_t b);
            void start_();
            void stop_();

            void apply_flags_();

            GPIOPin *dio_pin_;
            GPIOPin *clk_pin_;
            uint8_t intensity_;
            uint8_t length_;
            optional<tm1640_writer_t> writer_{};
            uint8_t buffer_[16] = {0};
        };

    } // namespace tm1640
} // namespace esphome
