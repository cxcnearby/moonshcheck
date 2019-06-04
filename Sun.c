#include <math.h>
#include <stdio.h>
#include <string.h>
//#include"ybj.h"

#define sun_C 1.0015174
#define sun_S 0.9948174

/********** Sun Orbit **********/

void sun_orbit(double mjd, double *SRAS, double *SDEC) {

  double sras[32][3] = {
      {-0.00002, 36003.0, 113.0},  {-0.00002, 108001.0, 289.0},
      {0.00003, 31557.0, 161.0},   {0.00003, 2281.0, 221.0},
      {0.00003, 29930.0, 48.0},    {0.00003, 3.0, 296.0},
      {0.00003, 73936.0, 166.0},   {0.00003, 155.0, 118.0},
      {0.00004, 33718.0, 316.0},   {0.00005, 3035.0, 110.0},
      {0.00005, 65929.0, 45.0},    {0.00005, 9038.0, 64.0},
      {0.00009, 22519.0, 352.0},   {0.00010, 216005.0, 333.0},
      {0.00010, 45038.0, 254.0},   {0.00012, 19.0, 159.0},
      {0.00012, 445267.0, 208.0},  {0.00013, 32964.0, 158.0},
      {0.00015, 144000.0, 286.0},  {-0.00019, 72002.0, 291.0},
      {0.00024, 180002.0, 309.0},  {0.00024, 108004.0, 134.0},
      {-0.00032, 35999.0, 268.0},  {0.00032, 1934.0, 145.0},
      {0.00133, 71998.1, 265.1},   {0.00353, 144003.1, 311.9},
      {0.00549, 108000.6, 288.5},  {0.00549, 36002.5, 113.4},
      {0.12764, 35999.05, 267.52}, {0.16419, 72001.539, 290.92},
      {18.69735, 0.0, 0.0},        {2400.05130, 0.0, 0.0}};

  double sdec[23][3] = {
      {0.0003, 180000.0, 206.0},      {0.0003, 9037.0, 332.0},
      {0.0003, 13482.0, 293.0},       {0.0003, 409266.0, 287.0},
      {0.0003, 36020.0, 80.0},        {0.0003, 35982.0, 121.0},
      {0.0003, 481268.0, 128.0},      {-0.0003, 108002.0, 211.0},
      {0.0004, 3036.0, 123.0},        {0.0004, 68965.0, 78.0},
      {0.0008, 35997.0, 345.0},       {-0.0012, 2.0, 13.0},
      {-0.0012, 72000.0, 188.0},      {0.0022, 37935.0, 65.0},
      {0.0031, 180004.0, 232.0},      {0.0073, 107999.0, 186.0},
      {0.0082, 144001.0, 209.0},      {0.0082, 72003.0, 34.0},
      {-0.0127, 36001.0, 190.0},      {0.1646, 108002.3, 211.4},
      {0.3886, 71999.82, 187.99},     {0.3888, 1.72, 12.94},
      {23.2643, 36000.7696, 190.4602}};

  /*
  double para[9][3] = {
    {0.000005,	33718.0,	226.0},
    {0.000005,	22519.0,	233.0},
    {0.000016,	45038.0,	164.0},
    {0.000016,	32964.0,	68.0},
    {0.000031,	445267.0,	298.0},
    {-0.000042,	35999.0,	178.0},
    {0.000139,	71998.0,	175.0},
    {0.016706,	35999.05,	177.53},
    {1.000140,	0.0,		0.0}
  };
  */

  double T, dt;
  int i, j, k;
  double s1, s2, s3;
  double mod1, mod2, mod3;
  double SUMD = 0.0;
  double SUMR = 0.0;
  double SUMP = 0.0;
  double ram, bet;
  double de, e0, e;
  double cr, sr, cb, sb, ce, se;
  double RAS, DEC, SSRAS;
  double u, v, w;
  double g, n, m;
  double theta, gamma;
  double gmst0, tu, z;

  dt = 58.0 + 0.8 * (2000.0 - 1990.0);
  T = (mjd / 36525.0) - (51544.5 / 36525.0) + (dt / 3600.0 / 24.0 / 36525.0);

  for (i = 0; i < 32; i++) {

    mod1 = sras[i][1] * T - ((int)(sras[i][1] * T / 360.0)) * 360.0;

    s1 = sras[i][0] * cos((mod1 + sras[i][2]) * deg_rad);
    if (i == 0 || i == 1 || i == 19 || i == 22 || i == 31)
      s1 = sras[i][0] * T * cos((mod1 + sras[i][2]) * deg_rad);

    SUMR += s1;
  }

  for (j = 0; j < 23; j++) {

    mod2 = sdec[j][1] * T - ((int)(sdec[j][1] * T / 360.0)) * 360.0;

    s2 = sdec[j][0] * cos((mod2 + sdec[j][2]) * deg_rad);
    if (j == 7 || j == 11 || j == 12 || j == 18)
      s2 = sdec[j][0] * T * cos((mod2 + sdec[j][2]) * deg_rad);

    SUMD += s2;
  }

  /* sisa no keisan
  for( k = 0; k < 9 ; k++){

    mod3 = para[k][1] * T - ( (int) ( para[k][1] * T / 360.0 ) ) * 360.0;
    s3 = para[k][0] * cos ( ( mod3 + para[k][2] ) * D2R );
    if( k == 5 ) s3 = para[k][0] * T * cos ( ( mod3 + para[k][2] ) * D2R );

    SUMP += s3;
  }


  de = 0.00256 * cos( ( 1934.0 * T + 235.0 ) * D2R ) + 0.00015 * cos( ( 72002.0
  * T + 201.0 ) * D2R ); e0 = 23.43928 - 0.01301 * T; e = e0 + de;

  ce = cos( e * D2R );
  se = sin( e * D2R );
  SSRAS = SUMR * 360.0 / 24.0;
  SSRAS = SSRAS - floor(SSRAS/360.0)*360.0;
  cr = cos( SSRAS * D2R );
  sr = sin( SSRAS * D2R );
  cb = cos( SUMD * D2R );
  sb = sin( SUMD * D2R );

  u = cb * cr;
  v = cb * sr * ce - sb * se;
  w = cb * sr * se + sb * ce;

  RAS = atan2( v, u );
  DEC = atan2( w, sqrt( u * u + v * v ) );
  */

  *SRAS = SUMR * 360.0 / 24.0;
  *SRAS = *SRAS - floor(*SRAS / 360.0) * 360.0;
  *SDEC = SUMD;

  /*
   tu = (mjd - 51544.5) / 36525.0;
   gmst0 = 0.279057273263889 + 100.002139037801 * tu
     + 1.07759259e-6 * tu * tu - 7.1759259e-11 * tu * tu * tu;

   z = (1.0 + (mjd - floor(mjd)) + gmst0) * 360.0;

   g = z + TIBET_LO;
   theta = ( g - floor( g / 360.0 ) * 360.0 ) * D2R;

   m = sin( SUMP * D2R ) * sun_C * cos( TIBET_LA * D2R ) / cos( DEC );

   *SRAS = ( atan( m * sin( RAS - theta ) / ( 1 - m * cos( RAS - theta ) ) ) +
   RAS ) * R2D;

   if( *SRAS < 0.0) *SRAS += 360.0;
   if( *SRAS > 360.0) *SRAS -= 360.0;

   gamma = atan( sun_S / sun_C * tan( TIBET_LA * D2R ) * cos( ( *SRAS * D2R -
   RAS ) / 2.0 ) / cos( ( *SRAS * D2R + RAS ) / 2.0 - theta ) ); n = sin( SUMP *
   D2R ) * sun_S * sin( TIBET_LA * D2R ) / sin( gamma );

   *SDEC = ( atan( n * sin( DEC - gamma ) / ( 1 - n * cos( DEC - gamma ) ) ) +
   DEC ) * R2D;
   */
}
