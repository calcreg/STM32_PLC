void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void BLINKOUT10_init__(BLINKOUT10 *data__, BOOL retain) {
  __INIT_EXTERNAL(BOOL,REDLED,data__->REDLED,retain)
  __INIT_EXTERNAL(BOOL,ORANGELED,data__->ORANGELED,retain)
  __INIT_EXTERNAL(BOOL,IN1,data__->IN1,retain)
  __INIT_EXTERNAL(STRING,LCDTEXT,data__->LCDTEXT,retain)
  UINT i;
  data__->__nb_steps = 7;
  static const STEP temp_step = {{0, 0}, 0, {{0, 0}, 0}};
  for(i = 0; i < data__->__nb_steps; i++) {
    data__->__step_list[i] = temp_step;
  }
  __SET_VAR(data__->,__step_list[0].X,,1);
  data__->__nb_actions = 4;
  static const ACTION temp_action = {0, {0, 0}, 0, 0, {0, 0}, {0, 0}};
  for(i = 0; i < data__->__nb_actions; i++) {
    data__->__action_list[i] = temp_action;
  }
  data__->__nb_transitions = 8;
  data__->__lasttick_time = __CURRENT_TIME;
}

// Steps definitions
#define INITIAL __step_list[0]
#define __SFC_INITIAL 0
#define STEP1 __step_list[1]
#define __SFC_STEP1 1
#define STEP2 __step_list[2]
#define __SFC_STEP2 2
#define STEP6 __step_list[3]
#define __SFC_STEP6 3
#define STEP3 __step_list[4]
#define __SFC_STEP3 4
#define STEP4 __step_list[5]
#define __SFC_STEP4 5
#define STEP5 __step_list[6]
#define __SFC_STEP5 6

// Actions definitions
#define __SFC_STEP6_INLINE1 0
#define __SFC_STEP5_INLINE2 1
#define __SFC_REDLED 2
#define __SFC_ORANGELED 3

// Code part
void BLINKOUT10_body__(BLINKOUT10 *data__) {
  // Initialise TEMP variables

  INT i;
  TIME elapsed_time, current_time;

  // Calculate elapsed_time
  current_time = __CURRENT_TIME;
  elapsed_time = __time_sub(current_time, data__->__lasttick_time);
  data__->__lasttick_time = current_time;
  // Transitions initialization
  if (__DEBUG) {
    for (i = 0; i < data__->__nb_transitions; i++) {
      data__->__transition_list[i] = data__->__debug_transition_list[i];
    }
  }
  // Steps initialization
  for (i = 0; i < data__->__nb_steps; i++) {
    data__->__step_list[i].prev_state = __GET_VAR(data__->__step_list[i].X);
    if (__GET_VAR(data__->__step_list[i].X)) {
      data__->__step_list[i].T.value = __time_add(data__->__step_list[i].T.value, elapsed_time);
    }
  }
  // Actions initialization
  for (i = 0; i < data__->__nb_actions; i++) {
    __SET_VAR(data__->,__action_list[i].state,,0);
    data__->__action_list[i].set = 0;
    data__->__action_list[i].reset = 0;
    if (__time_cmp(data__->__action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) > 0) {
      data__->__action_list[i].set_remaining_time = __time_sub(data__->__action_list[i].set_remaining_time, elapsed_time);
      if (__time_cmp(data__->__action_list[i].set_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) <= 0) {
        data__->__action_list[i].set_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);
        data__->__action_list[i].set = 1;
      }
    }
    if (__time_cmp(data__->__action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) > 0) {
      data__->__action_list[i].reset_remaining_time = __time_sub(data__->__action_list[i].reset_remaining_time, elapsed_time);
      if (__time_cmp(data__->__action_list[i].reset_remaining_time, __time_to_timespec(1, 0, 0, 0, 0, 0)) <= 0) {
        data__->__action_list[i].reset_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);
        data__->__action_list[i].reset = 1;
      }
    }
  }

  // Transitions fire test
  if (__GET_VAR(data__->INITIAL.X)) {
    __SET_VAR(data__->,__transition_list[0],,__GET_EXTERNAL(data__->IN1,));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[0],,__GET_VAR(data__->__transition_list[0]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[0],,__GET_EXTERNAL(data__->IN1,));
    }
    __SET_VAR(data__->,__transition_list[0],,0);
  }
  if (__GET_VAR(data__->STEP1.X)) {
    __SET_VAR(data__->,__transition_list[1],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP1.T,), __time_to_timespec(1, 500, 0, 0, 0, 0)));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[1],,__GET_VAR(data__->__transition_list[1]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[1],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP1.T,), __time_to_timespec(1, 500, 0, 0, 0, 0)));
    }
    __SET_VAR(data__->,__transition_list[1],,0);
  }
  if (__GET_VAR(data__->STEP2.X)) {
    __SET_VAR(data__->,__transition_list[2],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP2.T,), __time_to_timespec(1, 500, 0, 0, 0, 0)));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[2],,__GET_VAR(data__->__transition_list[2]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[2],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP2.T,), __time_to_timespec(1, 500, 0, 0, 0, 0)));
    }
    __SET_VAR(data__->,__transition_list[2],,0);
  }
  if (__GET_VAR(data__->STEP6.X)) {
    __SET_VAR(data__->,__transition_list[3],,__BOOL_LITERAL(TRUE));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[3],,__GET_VAR(data__->__transition_list[3]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[3],,__BOOL_LITERAL(TRUE));
    }
    __SET_VAR(data__->,__transition_list[3],,0);
  }
  if (__GET_VAR(data__->INITIAL.X)) {
    __SET_VAR(data__->,__transition_list[4],,!(__GET_EXTERNAL(data__->IN1,)));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[4],,__GET_VAR(data__->__transition_list[4]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[4],,!(__GET_EXTERNAL(data__->IN1,)));
    }
    __SET_VAR(data__->,__transition_list[4],,0);
  }
  if (__GET_VAR(data__->STEP3.X)) {
    __SET_VAR(data__->,__transition_list[5],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP3.T,), __time_to_timespec(1, 250, 0, 0, 0, 0)));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[5],,__GET_VAR(data__->__transition_list[5]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[5],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP3.T,), __time_to_timespec(1, 250, 0, 0, 0, 0)));
    }
    __SET_VAR(data__->,__transition_list[5],,0);
  }
  if (__GET_VAR(data__->STEP4.X)) {
    __SET_VAR(data__->,__transition_list[6],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP4.T,), __time_to_timespec(1, 750, 0, 0, 0, 0)));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[6],,__GET_VAR(data__->__transition_list[6]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[6],,GE_TIME(__BOOL_LITERAL(TRUE), NULL, 2, __GET_VAR(data__->STEP4.T,), __time_to_timespec(1, 750, 0, 0, 0, 0)));
    }
    __SET_VAR(data__->,__transition_list[6],,0);
  }
  if (__GET_VAR(data__->STEP5.X)) {
    __SET_VAR(data__->,__transition_list[7],,__BOOL_LITERAL(TRUE));
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[7],,__GET_VAR(data__->__transition_list[7]));
    }
  }
  else {
    if (__DEBUG) {
      __SET_VAR(data__->,__debug_transition_list[7],,__BOOL_LITERAL(TRUE));
    }
    __SET_VAR(data__->,__transition_list[7],,0);
  }

  // Transitions reset steps
  if (__GET_VAR(data__->__transition_list[0])) {
    __SET_VAR(data__->,INITIAL.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[1])) {
    __SET_VAR(data__->,STEP1.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[2])) {
    __SET_VAR(data__->,STEP2.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[3])) {
    __SET_VAR(data__->,STEP6.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[4])) {
    __SET_VAR(data__->,INITIAL.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[5])) {
    __SET_VAR(data__->,STEP3.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[6])) {
    __SET_VAR(data__->,STEP4.X,,0);
  }
  if (__GET_VAR(data__->__transition_list[7])) {
    __SET_VAR(data__->,STEP5.X,,0);
  }

  // Transitions set steps
  if (__GET_VAR(data__->__transition_list[0])) {
    __SET_VAR(data__->,STEP1.X,,1);
    data__->STEP1.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[1])) {
    __SET_VAR(data__->,STEP2.X,,1);
    data__->STEP2.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[2])) {
    __SET_VAR(data__->,STEP6.X,,1);
    data__->STEP6.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[3])) {
    __SET_VAR(data__->,INITIAL.X,,1);
    data__->INITIAL.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[4])) {
    __SET_VAR(data__->,STEP3.X,,1);
    data__->STEP3.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[5])) {
    __SET_VAR(data__->,STEP4.X,,1);
    data__->STEP4.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[6])) {
    __SET_VAR(data__->,STEP5.X,,1);
    data__->STEP5.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }
  if (__GET_VAR(data__->__transition_list[7])) {
    __SET_VAR(data__->,INITIAL.X,,1);
    data__->INITIAL.T.value = __time_to_timespec(1, 0, 0, 0, 0, 0);
  }

  // Steps association
  // STEP1 action associations
  {
    char active = __GET_VAR(data__->STEP1.X);
    char activated = active && !data__->STEP1.prev_state;
    char desactivated = !active && data__->STEP1.prev_state;

    if (active)       {data__->__action_list[__SFC_REDLED].set = 1;}

  }

  // STEP2 action associations
  {
    char active = __GET_VAR(data__->STEP2.X);
    char activated = active && !data__->STEP2.prev_state;
    char desactivated = !active && data__->STEP2.prev_state;

    if (active)       {data__->__action_list[__SFC_REDLED].reset = 1;}

  }

  // STEP6 action associations
  {
    char active = __GET_VAR(data__->STEP6.X);
    char activated = active && !data__->STEP6.prev_state;
    char desactivated = !active && data__->STEP6.prev_state;

    if (active)       {data__->__action_list[__SFC_STEP6_INLINE1].set = 1;}

  }

  // STEP3 action associations
  {
    char active = __GET_VAR(data__->STEP3.X);
    char activated = active && !data__->STEP3.prev_state;
    char desactivated = !active && data__->STEP3.prev_state;

    if (active)       {data__->__action_list[__SFC_ORANGELED].set = 1;}

  }

  // STEP4 action associations
  {
    char active = __GET_VAR(data__->STEP4.X);
    char activated = active && !data__->STEP4.prev_state;
    char desactivated = !active && data__->STEP4.prev_state;

    if (active)       {data__->__action_list[__SFC_ORANGELED].reset = 1;}

  }

  // STEP5 action associations
  {
    char active = __GET_VAR(data__->STEP5.X);
    char activated = active && !data__->STEP5.prev_state;
    char desactivated = !active && data__->STEP5.prev_state;

    if (active)       {data__->__action_list[__SFC_STEP5_INLINE2].set = 1;}

  }


  // Actions state evaluation
  for (i = 0; i < data__->__nb_actions; i++) {
    if (data__->__action_list[i].set) {
      data__->__action_list[i].set_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);
      data__->__action_list[i].stored = 1;
    }
    if (data__->__action_list[i].reset) {
      data__->__action_list[i].reset_remaining_time = __time_to_timespec(1, 0, 0, 0, 0, 0);
      data__->__action_list[i].stored = 0;
    }
    __SET_VAR(data__->,__action_list[i].state,,__GET_VAR(data__->__action_list[i].state) | data__->__action_list[i].stored);
  }

  // Actions execution
  if (data__->__action_list[__SFC_REDLED].reset) {
    __SET_EXTERNAL(data__->,REDLED,,0);
  }
  else if (data__->__action_list[__SFC_REDLED].set) {
    __SET_EXTERNAL(data__->,REDLED,,1);
  }
  if (data__->__action_list[__SFC_ORANGELED].reset) {
    __SET_EXTERNAL(data__->,ORANGELED,,0);
  }
  else if (data__->__action_list[__SFC_ORANGELED].set) {
    __SET_EXTERNAL(data__->,ORANGELED,,1);
  }
  if(__GET_VAR(data__->__action_list[__SFC_STEP6_INLINE1].state)) {
    __SET_EXTERNAL(data__->,LCDTEXT,,__STRING_LITERAL(5,"red\\n"));
  }

  if(__GET_VAR(data__->__action_list[__SFC_STEP5_INLINE2].state)) {
    __SET_EXTERNAL(data__->,LCDTEXT,,__STRING_LITERAL(8,"orange\\n"));
  }



  goto __end;

__end:
  return;
} // BLINKOUT10_body__() 

// Steps undefinitions
#undef INITIAL
#undef __SFC_INITIAL
#undef STEP1
#undef __SFC_STEP1
#undef STEP2
#undef __SFC_STEP2
#undef STEP6
#undef __SFC_STEP6
#undef STEP3
#undef __SFC_STEP3
#undef STEP4
#undef __SFC_STEP4
#undef STEP5
#undef __SFC_STEP5

// Actions undefinitions
#undef __SFC_STEP6_INLINE1
#undef __SFC_STEP5_INLINE2
#undef __SFC_REDLED
#undef __SFC_ORANGELED





