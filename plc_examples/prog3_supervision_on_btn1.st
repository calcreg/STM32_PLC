PROGRAM PLC_PRG
  VAR_EXTERNAL
    pwm_out     : WORD;
    relay       : BOOL;
    btn_green   : BOOL;
    btn_red     : BOOL;
    btn_yellow  : BOOL;
    LCDtext     : STRING;
    SV_BTNS     : WORD;
  END_VAR

  (* Declare constants as external to bring them into the POU scope *)
 VAR CONSTANT
    GRNB        : WORD := 1;
    REDB        : WORD := 2;
    YELB        : WORD := 4;
 END_VAR

VAR
    (* Variables internes et détection de fronts *)
    btn_yellow_last : BOOL := FALSE;
    btn_green_last  : BOOL := FALSE;
    duty_cycle      : INT := 0;      (* Valeur de 0 à 100 *)
    prog_running    : BOOL := TRUE;  (* État du programme *)
END_VAR

(* Si le programme est running*)
IF prog_running THEN

    (* --- BOUTON VERT : Activation relais + Message --- *)

    IF btn_green OR ((SV_BTNS AND GRNB) <> 0) THEN
        relay := TRUE;
        LCDtext := 'Green Btn OK';
    ELSE
        relay := FALSE;
        IF NOT btn_green AND btn_green_last THEN
           LCDtext := 'RELAY OFF';
        END_IF;
    END_IF;
    btn_green_last := btn_green;

    (* --- BOUTON JAUNE : Incrémentation PWM + Message --- *)
    (* Détection de 1 front montant (pression unique) *)
    IF (btn_yellow OR ((SV_BTNS AND YELB) <> 0)) AND NOT btn_yellow_last THEN
        
        (* Augmentation du duty cycle par pas de 10% avec plafond à 100% *)
        IF duty_cycle <= 100 THEN
            duty_cycle := duty_cycle + 10;
            IF duty_cycle > 100 THEN
                duty_cycle := 0;
            END_IF;
        END_IF;

        (* Application de la valeur sur la sortie PWM %QW0 *)
        pwm_out := INT_TO_WORD(DINT_TO_INT(INT_TO_DINT(duty_cycle) * 65535 / 100));

        (* dynamic Concatenation : "X% duty_cycle" *)
        LCDtext := CONCAT(INT_TO_STRING(duty_cycle), '% duty cycle');

    END_IF;
    btn_yellow_last := btn_yellow; (* Mémorisation état précédent *)

    (* --- BOUTON ROUGE : Arrêt du programme --- *)
    IF btn_red OR ((SV_BTNS AND REDB) <> 0) THEN
        relay := FALSE;
        pwm_out := 0;
        LCDtext := 'Program ended';
        prog_running := FALSE; (* Désactive le traitement principal *)
    END_IF;

END_IF;

END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      (* Entrées physiques *)
      btn_green  AT %IX0.0 : BOOL;
      btn_red    AT %IX0.1 : BOOL;
      btn_yellow AT %IX0.2 : BOOL;

      (* Sorties physiques *)
      relay      AT %QX0.1 : BOOL;
      pwm_out    AT %QW0   : WORD;

      (* Global variable bound to memory location %MW0 for hardware_layer.cpp *)
      LCDtext    AT %MW0   : STRING  := 'PROG3 PWM+SVBTN1';

      (* SuperVision Vars for Remote Control *)
      (* SV_BTNS : bits 0 (BTN1), bit1 (BTN2), bit2 (BTN3) *)
      SV_BTNS    AT %MW32  : WORD := 0;
    END_VAR

    TASK TaskMain(INTERVAL := T#50ms, PRIORITY := 0);
    PROGRAM Inst0 WITH TaskMain : PLC_PRG;
  END_RESOURCE

END_CONFIGURATION

