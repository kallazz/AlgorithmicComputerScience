package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;
import eu.jpereira.trainings.designpatterns.structural.adapter.model.Door;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeCodeForUnlockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotUnlockDoorException;

public class ThirdPartyDoorAdapter extends ThirdPartyDoor implements Door {
    @Override
    public void open(String code) throws IncorrectDoorCodeException {
        try {
            unlock(code);
        } catch (CannotUnlockDoorException ex) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public void close() {
        lock();
    }

    @Override
    public boolean isOpen() {
        final LockStatus currentLockStatus = getLockStatus();
        if (currentLockStatus == LockStatus.UNLOCKED) {
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void changeCode(String oldCode, String newCode, String newCodeConfirmation)
			throws IncorrectDoorCodeException, CodeMismatchException {
        if (newCode != newCodeConfirmation) {
            throw new CodeMismatchException();
        }

        try {
            unlock(oldCode);
            setNewLockCode(newCode);
        } catch (CannotUnlockDoorException | CannotChangeCodeForUnlockedDoor ex) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public boolean testCode(String code) {
        final LockStatus initialLockStatus = getLockStatus();
        try {
            unlock(code);
            if (getLockStatus() != initialLockStatus) {
                lock();
            }
        } catch (CannotUnlockDoorException ex) {
            return false;
        }

        return true;
    }
}
