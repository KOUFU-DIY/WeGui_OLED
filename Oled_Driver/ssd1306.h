/*
	Copyright 2025 Lu Zhihao

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef __SSD1306_H__
#define __SSD1306_H__




void SSD1306Set_Address_x(unsigned char x);
void SSD1306_Set_Address_ypage(unsigned char page);
void SSD1306_Set_Address_x_ypage(unsigned char x,unsigned char page);
void SSD1306_Init(void);




	
	
#endif

