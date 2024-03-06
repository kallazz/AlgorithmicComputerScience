package eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty;

import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.CodeMismatchException;
import eu.jpereira.trainings.designpatterns.structural.adapter.exceptions.IncorrectDoorCodeException;
import eu.jpereira.trainings.designpatterns.structural.adapter.model.Door;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.ThirdPartyDoor.LockStatus;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotChangeCodeForUnlockedDoor;
import eu.jpereira.trainings.designpatterns.structural.adapter.thirdparty.exceptions.CannotUnlockDoorException;

public class ThirdPartyDoorObjectAdapter implements Door {
    private ThirdPartyDoor door;

    public ThirdPartyDoorObjectAdapter() {
        door = new ThirdPartyDoor();
    }

    @Override
    public void open(String code) throws IncorrectDoorCodeException {
        try {
            door.unlock(code);
        } catch (CannotUnlockDoorException ex) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public void close() {
        door.lock();
    }

    @Override
    public boolean isOpen() {
        final LockStatus currentLockStatus = door.getLockStatus();
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
            door.unlock(oldCode);
            door.setNewLockCode(newCode);
        } catch (CannotUnlockDoorException | CannotChangeCodeForUnlockedDoor ex) {
            throw new IncorrectDoorCodeException();
        }
    }

    @Override
    public boolean testCode(String code) {
        final LockStatus initialLockStatus = door.getLockStatus();
        try {
            door.unlock(code);
            if (door.getLockStatus() != initialLockStatus) {
                door.lock();
            }
        } catch (CannotUnlockDoorException ex) {
            return false;
        }

        return true;
    }
}
