/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#ifndef POWERMONITOR_DATATYPES_H_
#define POWERMONITOR_DATATYPES_H_


// define the Shared Data Message Ids
typedef enum {
    INVALID_RAIL_VALUE,
    GET_RAIL_VALUE_ID,
    SET_RAIL_VALUE_ID,
    INITIAL_RAIL_VALUE_ID,
} msgIdE;

// define the data types
typedef enum {
    INVALID_FORMAT_TYPE,
    PMBUS_LINEAR16,     // default data format
    PMBUS_LINEAR11,
    XADC_VOLTAGE_SUPPLY,
    XADC_TEMPERATURE,
} dataFormatE;

// define the rail types
typedef enum {
    INVALID_DATA_TYPE,
    VOLTAGE,            // default data type
    CURRENT,
    POWER,
    TEMPERATURE,
} dataTypeE;

#endif /* POWERMONITOR_DATATYPES_H_ */
