#! /bin/bash

echo "START BASH"
allok=false
dirname=([0]="input_decryption" [1]="crypt" [2]="output_encryption")
cryptionprogram="crypt2withoutprintf"
cryptionmode="e"
if ([ -d ${dirname[0]} ]) && ([ -d ${dirname[1]} ]) && ([ -d ${dirname[2]} ]); then
	FILE=""
	DIR="./"${dirname[0]}
	if [ "$(ls -A $DIR)" ]; then
		DIR="./"${dirname[1]}
		if [ "$(ls -A $DIR)" ]; then
		  numfiles=(${dirname[1]}/*)
			numfiles=${#numfiles[@]}
			if [ $numfiles -eq 1 ]; then
			  allok=true
      else
				echo "Directory "${dirname[1]}" has more than 1 File!"
			fi
		else
			echo "Directory "${dirname[1]}" is empty. There should be 1 file"
		fi
	else

		echo "Directory "${dirname[0]}" is empty. There should be at last 1 file."
	fi
else
	echo "A/Some Dir\(s\) is/are missing!"
fi

case $allok in
  (true)
  if [ -d ${dirname[1]}/* ]; then
  	echo "In Directory must be a File, not a other Directory!"
  else
  	for filename in ${dirname[0]}/*; do
        if [ -f "$filename" ]; then
        	onlyfilename=$(basename $filename)
        	./$cryptionprogram ${dirname[0]}/$onlyfilename ${dirname[1]}/t $cryptionmode ${dirname[2]}/$onlyfilename
        else
        	echo $filename" "${dirname[1]}"/t"$cryptionmode" "${dirname[2]}"/"$filename
        fi
	done
  fi;;
  (false)  ;;
esac
echo "FINISH BASH"