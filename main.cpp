#include "mbed.h"

SPI spi(PF_9, PF_8, PF_7); // mosi, miso, sclk
DigitalOut cs(PC_1);

// Documents
// Manual for dev board:https://www.st.com/resource/en/user_manual/um1670-discovery-kit-with-stm32f429zi-mcu-stmicroelectronics.pdf
// gyroscope datasheet:https://www.mouser.com/datasheet/2/389/dm00168691-1798633.pdf

// Read a register on the gyroscope
int main() {
    // Chip must be deselected
    cs = 1;

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8,3);
    spi.frequency(1000000);
    int i=0;

    int16_t x_h[40];
    int16_t y_h[40];
    int16_t z_h[40];
    int16_t x_l[40];
    int16_t y_l[40];
    int16_t z_l[40];
    int16_t x[40];
    int16_t y[40];
    int16_t z[40];
    int16_t x_r[40],y_r[40],z_r[40];
    
int16_t res_w[40],v[40];
    int16_t sum_v=0, tot_dist;
    while (i<=40) {
     
      // Select the device by setting chip select low
      cs = 0;

      // Send 0x8f, the command to write to control register
      //spi.write(0x20);
      spi.write(0x20);
      int ctrl = spi.write(0x0F);

      cs=1;
      cs=0;

      spi.write(0xA8);
      x_h[i] = spi.write(0x00);

      cs=1;
      cs=0;
      spi.write(0xA9);
      x_l[i] = spi.write(0x00);
      x[i] = (x_h[i] << 8 ) | (x_l[i]); // Angular velocity in the x axis
      x_r[i] = x[i] / 57.3248; // Converting the angular velocity in the x axis from dps to radians per sec
      cs=1;
      cs=0;
      spi.write(0xAA);

      y_h[i] = spi.write(0x00);

      cs=1;
      cs=0;
      spi.write(0xAB);
      y_l[i]  = spi.write(0x00);
      y[i] = (y_h[i] << 8 ) | (y_l[i]); // Angular velocity in the y axis
      y_r[i] = y[i] / 57.3248; // Converting the angular velocity in the y axis from dps to radians per sec
      cs=1;
      cs=0;
      spi.write(0xAC);
      z_h[i] = spi.write(0x00);

      cs=1;
      cs=0;
      spi.write(0xAD);
      z_l[i] = spi.write(0x00);
      z[i] = (z_h[i] << 8 ) | (z_l[i]); // Angular velocity in the z axis
      z_r[i] = z[i] / 57.3248; // Converting the angular velocity in the z axis from dps to radians per sec

      printf("angular velocity in x[%d] axis in radians per sec = %d\n",i, x_r[i]);
      printf("angular velocity in y[%d] axis in radians per sec = %d\n",i, y_r[i]);
      printf("angular velocity in z[%d] axis in radians per sec = %d\n",i, z_r[i]);

      res_w[i] = sqrt(pow(x_r[i],2) + pow(y_r[i],2) + pow(z_r[i],2)); // Calculate the resultant angular velocity
      v[i] = res_w[i] * 0.1; // Calculate the linear velocity using the formula v = w * r where w is the resultant angular velocity
      sum_v = sum_v + v[i];
      printf("linear velocity v[%d] in meters per sec= %d\n",i, v[i]);
      tot_dist = sum_v *0.5; // Calculate total distance travelled in 20s
      printf("The total distance travelled in 20s = %d", tot_dist);

      // Deselect the device
      cs = 1;

      i++;

      wait_us(500000);

    }


    
    

}