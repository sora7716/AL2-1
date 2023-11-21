#include "fullScreen.h"

bool isFullScreen = false;

void FullScreen(char keys[], char preKeys[]) {

	if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && !isFullScreen) {
		isFullScreen = true;
	}
	else if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && isFullScreen) {
		isFullScreen = false;
	}
	if (isFullScreen) {
		Novice::SetWindowMode(kFullscreen);
	}
	else {
		Novice::SetWindowMode(kWindowed);
	}

}
