int i = 0;
int j = 0;
int data_storage[50];
int U_present = 0;
void changing_string();
int total_no = 50;
int data = 0;
int black = 0;
int white = 1;
int total_correct_turn = 0;
int sensor_1 = 0;
int sensor_2 = 0;
int sensor_3 = 0;
int sensor_4 = 0;
int sensor_5 = 0;
int sensor_6 = 0;
int node = 0;
int delta_pwm = 0;
int delta_pwm1 = 0;
boolean line_present = false;
boolean all_high = false;
boolean t_node = false;
boolean autonomous_mode = false;
boolean waiting_key = false;
int left_pwm = 0;
int right_pwm = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);


}
void loop() {
  read_sensor();
  starting_position();
  stop_move();
  delay(10000);


}

void starting_position() {
  int flag = 0;
  while (flag == 0) {
    read_sensor();
    line_follower();
    node_detection();
    if (t_node) {
      left_turn();
      node = 0;
    }
    if (node == 4) {
      stop_move();
      right_turn();
      stop_move();
      delay(10000);
      flag = 1;
    }
  }
}

void node_detection() {
  t_node = false;
  if (sensor_5 == white) {
    long int timer = millis();
    while (millis() - timer < 300) {
      read_sensor();
      line_follower();
      if (sensor_1 == white) {
        node++;
        t_node = true;
        Serial.println("T point reached ");
        break;
      }
    }
    if (t_node == false) {
      node++;
    }
  }


  else if (sensor_1 == white) {
    long int timer = millis();
    while (millis() - timer < 300) {
      read_sensor();
      line_follower();
      if (sensor_5 == white) {
        node++;
        t_node = true;
        Serial.println("T point reached ");
        break;
      }
    }
    if (t_node == false) {
      node++;
    }
  }

}
void read_sensor() {
  sensor_1 = digitalRead(7);
  sensor_2 = digitalRead(3);
  sensor_3 = digitalRead(4);
  sensor_4 = digitalRead(5);
  sensor_5 = digitalRead(6);
  //sensor_6 = digitalRead(7);
  /*Serial.println("sensor   ");
  Serial.println(sensor_1);
  Serial.println(sensor_2);
  Serial.println(sensor_3);
  Serial.println(sensor_4);
  Serial.println(sensor_5);*/
  //Serial.println(sensor_6);
}

void check_run() {
  Serial.println("check_run  ");


  forward_move();
  delay(80);
  read_sensor();
  forward_move();
  delay(200);


  if (sensor_3 == white) {
    line_present = true;
    Serial.println("line_present");
  }
  else {
    line_present = false;
    Serial.println("line_absent   ");
  }
}
/*
 void check_run_for_plus_point(){
Serial.println("check_run for plus point ");
while(sensor_1==white && sensor_5 == white){
forward_move();
read_sensor();
}
forward_move();
delay(600);


if(sensor_3 == white){
line_present = true;
Serial.println("line_present");
}
else{
line_present = false;
Serial.println("line_absent   ");
}
if(sensor_1 == white && sensor_3==white && sensor_5 ==white){
all_high = true;
Serial.println("all_present");
}
}*/

void forward() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, left_pwm);

  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, right_pwm);


}
void forward_move() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, 150);

  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 150);


}
void backward() {
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(10, left_pwm);

  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, right_pwm);


}

void right_turn() {
  forward_move();
  delay(200);
  right();
  delay(600);
  read_sensor();
  while (sensor_3 != white ) {
    right();
    //Serial.println("right   ");
    read_sensor();
  }
}

void left_turn() {
  forward_move();
  delay(200);
  left();
  delay(600);
  while (sensor_3 != white ) {
    left();
    read_sensor();
    //Serial.println("left   ");
  }
}

void right() {
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  analogWrite(10, 90);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  analogWrite(11, 90);
}
void left() {
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  analogWrite(11, 90);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  analogWrite(10, 90);
}

void line_follower() {

  if (sensor_2 == white && sensor_4 == white)
  {
    delta_pwm = 0;
    delta_pwm1 = 0;
  }
  else if (sensor_2 == white) {
    delta_pwm += 30;
    if (delta_pwm > 100) {
      delta_pwm = 100;
    }
    delta_pwm1 = 0;
  }
  else if (sensor_4 == white) {
    delta_pwm1 += 30;
    if (delta_pwm1 > 100) {
      delta_pwm1 = 100;
    }
    delta_pwm = 0;
  }
  else {
    delta_pwm1 = 0 ;
    delta_pwm = 0;
  }
  left_pwm = 100 - delta_pwm;
  right_pwm = 100 - delta_pwm1;
 // Serial.println("left_pwm  "+String(left_pwm));
 // Serial.println("right_pwm  "+String(right_pwm));
  forward();
}

void u_turn() {

  stop_move();
  forward_move();
  delay(400);
  while (sensor_3 != white || sensor_5 != white || sensor_2 != white) {
    right();
    read_sensor();
    //Serial.println("u turn");
  }

}
void stop_move() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  analogWrite(10, 0);

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  analogWrite(11, 0);

}
