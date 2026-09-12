#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM BLINKOUT10
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,REDLED)
  __DECLARE_EXTERNAL(BOOL,ORANGELED)
  __DECLARE_EXTERNAL(BOOL,IN1)
  __DECLARE_EXTERNAL(STRING,LCDTEXT)
  STEP __step_list[7];
  UINT __nb_steps;
  ACTION __action_list[4];
  UINT __nb_actions;
  __IEC_BOOL_t __transition_list[8];
  __IEC_BOOL_t __debug_transition_list[8];
  UINT __nb_transitions;
  TIME __lasttick_time;

} BLINKOUT10;

void BLINKOUT10_init__(BLINKOUT10 *data__, BOOL retain);
// Code part
void BLINKOUT10_body__(BLINKOUT10 *data__);
#endif //__POUS_H
