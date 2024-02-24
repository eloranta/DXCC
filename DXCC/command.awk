NF==6  {print $NF "\t" $1 "\t\t" $2}
NF==7  {print $NF "\t" $1 "\t\t" $2 " " $3}
NF==8  {print $NF "\t" $1 "\t\t" $2 " " $3 " " $4}
NF==9  {print $NF "\t" $1 "\t\t" $2 " " $3 " " $4 " " $5}
NF==10 {print $NF "\t" $1 "\t\t" $2 " " $3 " " $4 " " $5 " " $6}
END {print NR}

