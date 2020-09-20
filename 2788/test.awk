{ 
	if($1 != "")
	{
		T++;
		printf "%s\t%s", $1, $2;
		if ($1 == $2)
		{
			L++;
			printf "\t\t -- OK\n";
		} else {
			printf "\t\t -- FAIL\n";
		}
	}
} 
END { 
	printf "\nRESULT: %d/%d - %5.2f%\n", L, T, 100*L/T;
}
