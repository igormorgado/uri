/*
 * Return the SDL_GameController associated with a player index.
 */
extern DECLSPEC SDL_GameController *SDLCALL SDL_GameControllerFromPlayerIndex(int player_index);

/**
 *  Get the player index of an opened game controller, or -1 if it's not available
 *
 *  For XInput controllers this returns the XInput user index.
 */
extern DECLSPEC int SDLCALL SDL_GameControllerGetPlayerIndex(SDL_GameController *gamecontroller);


/*  Returns SDL_TRUE if the controller has been opened and currently connected,
 *  or SDL_FALSE if it has not.
 */
extern DECLSPEC SDL_bool SDLCALL SDL_GameControllerGetAttached(SDL_GameController *gamecontroller);


