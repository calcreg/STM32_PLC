PROGRAM PWM_Tester
  VAR_EXTERNAL
    PWM1_Output : WORD;
    LCDText     : STRING; (* Global variable tied to %MD0 *)
  END_VAR

  VAR
    (* Timer to trigger state changes every 3 seconds *)
    StepTimer : TON;
    StepTimer_Q : BOOL;
    StepTimer_ET : TIME;
    
    (* Index tracking current duty cycle level (0 to 5) *)
    StepIndex : INT := 0;
  END_VAR

  (* -------------------------------------------------------------------
     1. TIMER LOGIC
     Runs continuously, pulsing StepTimer.Q high every 3.0 seconds
     ------------------------------------------------------------------- *)
  StepTimer(
    IN := NOT StepTimer.Q, 
    PT := T#3s, 
    Q => StepTimer_Q, 
    ET => StepTimer_ET
  );

  (* -------------------------------------------------------------------
     2. STATE INCREMENT
     Advance to the next duty cycle level when timer completes
     ------------------------------------------------------------------- *)
  IF StepTimer.Q THEN
    StepIndex := StepIndex + 1;
    IF StepIndex > 5 THEN
      StepIndex := 0; (* Wrap back to 0% *)
    END_IF;
  END_IF;

  (* -------------------------------------------------------------------
     3. DUTY CYCLE LOOKUP, OUTPUT DRIVE & LCD UPDATE
     ------------------------------------------------------------------- *)
  CASE StepIndex OF
    0:  
      PWM1_Output := UINT_TO_WORD(16#0000); (* 0% Duty *)
      LCDtext     := '0% Duty';
    1:  
      PWM1_Output := UINT_TO_WORD(16#1999); (* 10% Duty *)
      LCDtext     := '10% Duty';
    2:  
      PWM1_Output := UINT_TO_WORD(16#4CCD); (* 30% Duty *)
      LCDtext     := '30% Duty';
    3:  
      PWM1_Output := UINT_TO_WORD(16#7FFF); (* 50% Duty *)
      LCDtext     := '50% Duty';
    4:  
      PWM1_Output := UINT_TO_WORD(16#B332); (* 70% Duty *)
      LCDtext     := '70% Duty';
    5:  
      PWM1_Output := UINT_TO_WORD(16#FFFF); (* 100% Duty *)
      LCDtext     := '100% Duty';
  ELSE
    StepIndex   := 0;
    PWM1_Output := UINT_TO_WORD(16#0000);
    LCDText     := 'Unknown Case';
  END_CASE;

END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      (* Hardware output mapped at global configuration scope *)
      PWM1_Output AT %QW0 : WORD;

      (* Global variable bound to memory location %MD0 for hardware_layer.cpp *)
      LCDtext AT %MD0 : STRING := 'Test PWM1';
    END_VAR

    TASK TaskMain(INTERVAL := T#50ms, PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : PWM_Tester;
  END_RESOURCE

END_CONFIGURATION
