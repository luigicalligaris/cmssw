#include "CondFormats/Phase2TrackerObjects/interface/DTCId.h"

#include <string>
#include <functional>
#include <limits>

DTCId::DTCId() noexcept : dtc_number_(std::numeric_limits<unsigned short>::max()){}
DTCId::~DTCId() noexcept {}

DTCId::DTCId(DTCId const& rhs) noexcept : dtc_number_(rhs.dtc_number_){}
DTCId::DTCId(DTCId&&      rhs) noexcept : dtc_number_(rhs.dtc_number_){}
DTCId& DTCId::operator=(DTCId const& rhs) noexcept {dtc_number_ = rhs.dtc_number_; return *this;}
DTCId& DTCId::operator=(DTCId&&      rhs) noexcept {dtc_number_ = rhs.dtc_number_; return *this;}

DTCId::DTCId(unsigned short const dtc_number) noexcept : dtc_number_(dtc_number){}
DTCId& DTCId::operator=(unsigned short const dtc_number) noexcept {dtc_number_ = dtc_number; return *this;}

