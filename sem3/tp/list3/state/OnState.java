/**
 * Copyright 2011 Joao Miguel Pereira
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
package eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state;

/**
 * @author jpereira
 *
 *TODO: Find TODOs in this file and complete them
 */
public class OnState implements ApplianceStateBehavior {

	/* (non-Javadoc)
	 * @see eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceStateBehavior#getState()
	 */
	@Override
	public ApplianceState getState() {
		//TODO: return the correnponding state enum. This represents the ON State, so return ApplianceState.ON;
		return ApplianceState.ON;
	}

	/* (non-Javadoc)
	 * @see eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceStateBehavior#start()
	 */
	@Override
	public ApplianceStateBehavior start() {
		//TODO: return the STARTED Behavior ApplianceState.STARTED.getStateBehavior()
		return ApplianceState.STARTED.getStateBehavior();
		
	}

	/* (non-Javadoc)
	 * @see eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceStateBehavior#stop()
	 */
	@Override
	public ApplianceStateBehavior stop() {
		//Can't stop from ON state
		return this;
	}

	/* (non-Javadoc)
	 * @see eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceStateBehavior#turnOn()
	 */
	@Override
	public ApplianceStateBehavior turnOn() {
		//Already on
		return this;
	}

	/* (non-Javadoc)
	 * @see eu.jpereira.trainings.designpatterns.behavioral.state.appliance.state.ApplianceStateBehavior#turnOff()
	 */
	@Override
	public ApplianceStateBehavior turnOff() {
		//Go Off
		return ApplianceState.OFF.getStateBehavior();
	}

}
