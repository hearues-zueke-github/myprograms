#include "encraption.h"

#define NUMBER_ALGORITHM 8

void algorithmEncrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt)
{
  int pasta;
  int noodles, int sauce, int more_noodles;
  int temp_int;
  int i_dont_know_how_to_name_this, i_also_dont_know_how_to_name_this, i_really_dont_know_how_to_name_this;
  pasta = 0;
  i_really_dont_know_how_to_name_this = (array_length_in > 255 ? 255 : array_length_in / 2);
  while (pasta < array_length_crypt - 1)
  {
    i_dont_know_how_to_name_this = ((int)(array_crypt[pasta] & 0xFF)) % NUMBER_ALGORITHM;
    i_also_dont_know_how_to_name_this = ((int)(array_crypt[pasta + 1] & 0xFF)) % ((int)(i_really_dont_know_how_to_name_this)) + 1;
    switch (i_dont_know_how_to_name_this)
    {
      case 0:
        noodles = 0;
        while (noodles + i_also_dont_know_how_to_name_this < array_length_in)
        {
          temp_int = array_in[noodles];
          array_in[noodles] = array_in[noodles + i_also_dont_know_how_to_name_this];
          array_in[noodles + i_also_dont_know_how_to_name_this] = temp_int;
          noodles++;
        }
      break;

      case 1:
        noodles = array_length_in - 1;
        while (noodles - i_also_dont_know_how_to_name_this >= 0)
        {
          temp_int = array_in[noodles];
          array_in[noodles] = array_in[noodles - i_also_dont_know_how_to_name_this];
          array_in[noodles - i_also_dont_know_how_to_name_this] = temp_int;
          noodles--;
        }
      break;

      case 2:
        noodles = 0;
        sauce = 1;
        while (noodles < array_length_in)
        {
          temp_int = 255 - array_in[noodles];
          if (temp_int >= sauce)
          {
            array_in[noodles] = array_in[noodles] + sauce;
          }
          else
          {
            array_in[noodles] = sauce - temp_int - 1;
          }
          noodles++;
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
        }
      break;

      case 3:
        noodles = array_length_in - 1;
        sauce = 1;
        while (noodles >= 0)
        {
          temp_int = 255 - array_in[noodles];
          if (temp_int >= sauce)
          {
            array_in[noodles] = array_in[noodles] + sauce;
          }
          else
          {
            array_in[noodles] = sauce - temp_int - 1;
          }
          noodles--;
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
        }
      break;

      case 4:
        noodles = 0;
        sauce = 1;
        while (noodles < array_length_in - 2)
        {
          if ((noodles + sauce) < array_length_in)
          {
            temp_int = array_in[noodles];
            array_in[noodles] = array_in[noodles + sauce];
            array_in[noodles + sauce] = temp_int;
          }
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
          noodles++;
        }
      break;

      case 5:
        noodles = array_length_in - 1;
        sauce = 1;
        while (noodles > 0)
        {
          if ((noodles - sauce) >= 0)
          {
            temp_int = array_in[noodles];
            array_in[noodles] = array_in[noodles - sauce];
            array_in[noodles - sauce] = temp_int;
          }
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
          noodles--;
        }
      break;

      case 6:
        noodles = 0;
        sauce = 0;
        more_noodles = 1;
        while (noodles < array_length_in)
        {
          array_in[noodles] += more_noodles;
          more_noodles++;
          if (more_noodles > sauce + 1)
          {
            more_noodles = 1;
            sauce++;
            if (sauce >= i_also_dont_know_how_to_name_this)
            {
              sauce = 0;
            }
          }
          noodles++;
        }
      break;

      case 7:
        noodles = array_length_in - 1;
        sauce = 0;
        more_noodles = 1;
        while (noodles >= 0)
        {
          array_in[noodles] += more_noodles;
          more_noodles++;
          if (more_noodles > sauce + 1)
          {
            more_noodles = 1;
            sauce++;
            if (sauce >= i_also_dont_know_how_to_name_this)
            {
              sauce = 0;
            }
          }
          noodles--;
        }
      break;
    }
    pasta += 2;
  }
}

void algorithmDecrypt(unsigned char *array_in, int array_length_in, unsigned char *array_crypt, int array_length_crypt)
{
  int pasta;
  int noodles;
  int sauce;
  int more_noodles;
  int temp_int;
  int i_dont_know_how_to_name_this;
  int i_also_dont_know_how_to_name_this;
  int i_really_dont_know_how_to_name_this;
  pasta = (array_length_crypt / 2) * 2 - 2;
  i_really_dont_know_how_to_name_this = (array_length_in > 255 ? 255 : array_length_in / 2);
  while (pasta >= 0)
  {
    i_dont_know_how_to_name_this = ((int)(array_crypt[pasta] & 0xFF)) % NUMBER_ALGORITHM;
    i_also_dont_know_how_to_name_this = ((int)(array_crypt[pasta + 1] & 0xFF)) % ((int)(i_really_dont_know_how_to_name_this)) + 1;
    switch (i_dont_know_how_to_name_this)
    {
      case 0:
        noodles = array_length_in - 1;
        while (noodles - i_also_dont_know_how_to_name_this >= 0)
        {
          temp_int = array_in[noodles];
          array_in[noodles] = array_in[noodles - i_also_dont_know_how_to_name_this];
          array_in[noodles - i_also_dont_know_how_to_name_this] = temp_int;
          noodles--;
        }
      break;

      case 1:
        noodles = 0;
        while (noodles + i_also_dont_know_how_to_name_this < array_length_in)
        {
          temp_int = array_in[noodles];
          array_in[noodles] = array_in[noodles + i_also_dont_know_how_to_name_this];
          array_in[noodles + i_also_dont_know_how_to_name_this] = temp_int;
          noodles++;
        }
      break;

      case 2:
        noodles = 0;
        sauce = 1;
        while (noodles < array_length_in)
        {
          array_in[noodles] -= sauce;
          noodles++;
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
        }
      break;

      case 3:
        noodles = array_length_in - 1;
        sauce = 1;
        while (noodles >= 0)
        {
          array_in[noodles] -= sauce;
          noodles--;
          sauce++;
          if (sauce > i_also_dont_know_how_to_name_this)
          {
            sauce = 1;
          }
        }
      break;

      case 4:
        noodles = array_length_in - 1;
        if ((sauce = array_length_in % i_also_dont_know_how_to_name_this) == 0)
        {
          sauce = i_also_dont_know_how_to_name_this;
        }
        while (noodles >= 0)
        {
          if ((noodles + sauce) < array_length_in)
          {
            temp_int = array_in[noodles];
            array_in[noodles] = array_in[noodles + sauce];
            array_in[noodles + sauce] = temp_int;
          }
          sauce--;
          if (sauce < 1)
          {
            sauce = i_also_dont_know_how_to_name_this;
          }
          noodles--;
        }
      break;

      case 5:
        noodles = 0;
        if ((sauce = array_length_in % i_also_dont_know_how_to_name_this) == 0)
        {
          sauce = i_also_dont_know_how_to_name_this;
        }
        while (noodles <= array_length_in - 1)
        {
          if ((noodles - sauce) >= 0)
          {
            temp_int = array_in[noodles];
            array_in[noodles] = array_in[noodles - sauce];
            array_in[noodles - sauce] = temp_int;
          }
          sauce--;
          if (sauce < 1)
          {
            sauce = i_also_dont_know_how_to_name_this;
          }
          noodles++;
        }
      break;

      case 6:
        noodles = 0;
        sauce = 0;
        more_noodles = 1;
        while (noodles < array_length_in)
        {
          array_in[noodles] -= more_noodles;
          more_noodles++;
          if (more_noodles > sauce + 1)
          {
            more_noodles = 1;
            sauce++;
            if (sauce >= i_also_dont_know_how_to_name_this)
            {
              sauce = 0;
            }
          }
          noodles++;
        }
      break;

      case 7:
        noodles = array_length_in - 1;
        sauce = 0;
        more_noodles = 1;
        while (noodles >= 0)
        {
          array_in[noodles] -= more_noodles;
          more_noodles++;
          if (more_noodles > sauce + 1)
          {
            more_noodles = 1;
            sauce++;
            if (sauce >= i_also_dont_know_how_to_name_this)
            {
              sauce = 0;
            }
          }
          noodles--;
        }
      break;
    }
    pasta -= 2;
  }
}
