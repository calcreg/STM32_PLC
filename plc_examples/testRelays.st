PROGRAM BlinkOUT10
  VAR_EXTERNAL
    REDLED : BOOL;
    ORANGELED : BOOL;
    RELAI0 : BOOL;
    RELAI1 : BOOL;
    RELAI2 : BOOL;
    IN1 : BOOL;
    LCDtext : STRING;
  END_VAR

  VAR
    IN1_prev : BOOL := FALSE;
    init_done : BOOL := FALSE;
    timer_red : TON;
    timer_orange : TON;
    led_state : BOOL := FALSE;
  END_VAR

  (* ------------------------------------------------------------- *)
  (* 1. INITIALIZATION ON FIRST SCAN                               *)
  (* ------------------------------------------------------------- *)
  IF NOT init_done THEN
    LCDtext := 'Loop Start';
    init_done := TRUE;
    IN1_prev := IN1;
  END_IF;

  (* ------------------------------------------------------------- *)
  (* 2. DYNAMIC LCD TEXT UPDATES (EDGE DETECTION)                 *)
  (* ------------------------------------------------------------- *)
  (* Detect Press (Rising Edge) *)
  IF IN1 AND NOT IN1_prev THEN
    LCDtext := 'Btn Pressed';
  END_IF;

  (* Detect Release (Falling Edge) *)
  IF NOT IN1 AND IN1_prev THEN
    LCDtext := 'Btn Released';
  END_IF;

  (* Store input state for next scan cycle *)
  IN1_prev := IN1;


  (* ------------------------------------------------------------- *)
  (* 3. LED & RELAY CONTROL LOGIC                                 *)
  (* ------------------------------------------------------------- *)
  IF IN1 THEN
    (* Flash RED LED and RELAI0 when button is pressed *)
    timer_red(IN := NOT timer_red.Q, PT := T#500ms);
    IF timer_red.Q THEN
      led_state := NOT led_state;
    END_IF;
    
    REDLED := led_state;
    RELAI0 := led_state;
    ORANGELED := FALSE;
    RELAI1 := FALSE;
  ELSE
    (* Flash ORANGE LED and RELAI1 when button is released *)
    timer_orange(IN := NOT timer_orange.Q, PT := T#1s);
    IF timer_orange.Q THEN
      led_state := NOT led_state;
    END_IF;
    
    ORANGELED := led_state;
    RELAI1 := led_state;
    REDLED := FALSE;
    RELAI0 := FALSE;
  END_IF;

END_PROGRAM


CONFIGURATION Config0
  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      REDLED AT %QX1.0 : BOOL;
      ORANGELED AT %QX1.1 : BOOL;
      RELAI0 AT %QX0.0 : BOOL;
      RELAI1 AT %QX0.1 : BOOL;
      RELAI2 AT %QX0.2 : BOOL;
      IN1 AT %IX0.0 : BOOL;
      LCDtext AT %MD0 : STRING := 'OpenPLC V3\n';
    END_VAR
    TASK task0(INTERVAL := T#20ms, PRIORITY := 0);
    PROGRAM instance0 WITH task0 : BlinkOUT10;
  END_RESOURCE
END_CONFIGURATION
