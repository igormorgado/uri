char board[21][21];
void build( int *len, char s[] ){

    char l;
    int x,y,k=0;
    scanf(" %d", len );
    scanf(" %d %d", &x, &y);
    x--;y--;

    s[k++] = board[x][y];
    for( int i = 0; i < (*len); i++ ){
        scanf(" %c", &l );

        if( l == 'N' ) x--;

        else if( l == 'S') x++;

        else if( l == 'E') y++;

        else y--;

        s[k++] = board[x][y];
    }
    s[k] = '\0';
    (*len) = k;
}

int main( void ){

    int t,h,w;
    scanf(" %d", &t );
    for( int c = 1; c <= t; c++ ){
        memset(memo,false,sizeof(memo));

        scanf(" %d %d", &h, &w );

        for( int i = 0; i < h; i++ ) scanf(" %s", board[i] );

        build(&len1,s1); build(&len2,s2);

        Stt ans = S(0,0);

        printf("Case %d: %d %d\n", c, ans.u1, ans.u2 );
    }

    return 0;
}
