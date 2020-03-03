byte Bitblue_ble_app::remote_control(int *speed, byte default_speed, byte *mode){
	while(_read_seq == 0){//code may stuck here until ljoystix info is in.
		read_data();
	}
	if(_read_seq == 1){ //need to add non directional! as result piggy back last state known
		for(int i=0, motor=0; motor<2; motor++){//add events where it is non direction //reset the values stored in the instruction array		
			if(_mod == 2){
				speed[motor] = default_speed;
			}
			else{
				if( _dis[motor]>0 ){
					i = (_dis[2]|_dis[3]) - (_dis[1]|_dis[0]);
					if(i<0){
						motor[speed] = (_dis[1]|_dis[0]) - (_dis[2]|_dis[3]);
					}
					else{
						motor[speed] = i;
					}
				}
				else{
					i = (_dis[2]|_dis[3]);
					motor[speed]=i;
				}
				if(i > 0){
					i=B10;
				}
				else if(i == 0){
					i=B00;
				}
				else{
					i=B01;
				}
				if(_dis[3] > _dis[2]){				//invert the insturction when joystix is at Z portion (back/reverse)
					i ^= B11;
				}
				_direction |= i;
				if(motor==0){
					_direction = _direction << 2;
					i=0;				
				}
			}
			//Serial.write("m");
			//Serial.print(motor);
			//Serial.write(":");
			//Serial.print(speed[motor]);
			//if(motor == 0){
			//	Serial.write(",");
			//}
		}
		//Serial.write("-");
		if(_mod == 2){
			if(_buf[0] == _k[0]){
			_direction = B0110;
			}
			else if(_buf[0] == _k[1]){
				_direction = B1001;
			}
			else if(_buf[0] == _k[2]){
				_direction = B1010;
			}
			else if(_buf[0] == _k[3]){
				_direction = B0101;
			}
			else if(_buf[0] == _k[4]){
				*mode = 4;
			}
			else if(_buf[0] == _k[5]){
				*mode = 5;
			}
			else if(_buf[0] == _k[6]){
				*mode = 0;
			}
			else if(_buf[0] == _k[7]){
				*mode = 1;
			}
			else if(_buf[0] == _k[8]){
				*mode = 2;
			}
			else{
				if(_buf[0] == _k[9]){
				*mode = 3;
				}
			}
		}
		//Serial.write("dir:");
		//Serial.print(_direction);
		_read_seq = 0;
		clear_data();
	}
	return _direction;
}

void Bitblue_ble_app::im_remote_control(byte *m_data){
	while(_read_seq == 0){//code may stuck here until ljoystix info is in.
		read_data();
	}
	if(_read_seq == 1){ //need to add non directional! as result piggy back last state known
		for(int i=0, motor=0; motor<2; motor++){//add events where it is non direction //reset the values stored in the instruction array		
			if(_mod == 2){
				if(_buf[0] == _k[0]){
					m_data[motor+3] += (B1 & motor);//
				}
				else if(_buf[0] == _k[1]){
					m_data[motor+3] += (B1 ^ motor);//
				}
				else if(_buf[0] == _k[2]){
					m_data[0] = B1010;
					if(m_data[motor+3]==0){
						m_data[motor+3]=1;
					}
					if(m_data[3]!=m_data[4]){
						if(m_data[3]<m_data[4]){
							m_data[3]=m_data[4];
						}
						else{
							m_data[4]=m_data[3];
						}
					}
				}
				else if(_buf[0] == _k[3]){
					m_data[0] = B0101;
					if(m_data[motor+3]==0){
						m_data[motor+3]=1;
					}
					if(m_data[3]!=m_data[4]){
						if(m_data[3]<m_data[4]){
							m_data[3]=m_data[4];
						}
						else{
							m_data[4]=m_data[3];
						}
					}
				}
				else if(_buf[0] == _k[6]){
					m_data[motor+3]--;
				}
				else{
					if(_buf[0] == _k[7]){
						m_data[motor+3]++;
					}
				}
				
				//m_data[motor+3] += (m_data[motor+1]/3);
			}
			else{
				if( _dis[motor]>0 ){ //this is to determine the pwm of the motor
					i = (_dis[2]|_dis[3]) - (_dis[1]|_dis[0]);
					if(i<0){
						m_data[motor+1] = (_dis[1]|_dis[0]) - (_dis[2]|_dis[3]);
						m_data[motor+3] = m_data[motor+1] / 3;
					}
					else{
						m_data[motor+1] = i;
					}
				}
				else{//this is to determine the pwm of the motor
					i = (_dis[2]|_dis[3]);
					m_data[motor+1] = i;
				}
				if(i > 0){	//determine the direction
					i=B10;
				}
				else if(i == 0){
					i=B00;
				}
				else{
					i=B01;
				}
				if(_dis[3] > _dis[2]){				//invert the insturction when joystix is at Z portion (back/reverse)
					i ^= B11;
				}
				m_data[0] |= i;
				if(motor==0){
					m_data[0] = m_data[0] << 2;
					i=0;				
				}
			}
			//Serial.write("m");
			//Serial.print(motor);
			//Serial.write(":");
			//Serial.print(speed[motor]);
			//if(motor == 0){
			//	Serial.write(",");
			//}
		}
		
		if(_buf[0] == _k[4]){
			m_data[0] = B0000;
		}
		else if(_buf[0] == _k[5]){
			m_data[0] = B0000;
		}
		else if(_buf[0] == _k[8]){
			m_data[0] = B0000;
		}
		else{
			if(_buf[0] == _k[9]){
				m_data[0] = B0000;
				m_data[1] = 0;
				m_data[2] = 0;
				m_data[3] = 0;
				m_data[4] = 0;
			}
		}
		//Serial.write("dir:");
		//Serial.print(_direction);
		_read_seq = 0;
		clear_data();
	}
}

/********************************************************
     * Functions will return direction instruction for	 	*
     * motor driver from bitblue controller app.			*
     ********************************************************/
    byte remote_control(int *speed, byte default_speed, byte *mode);

	//add mode selection
	
	void im_remote_control(byte *m_data);