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
package eu.jpereira.trainings.designpatterns.behavioral.observer.mapper;

import java.util.ArrayList;
import java.util.List;

import eu.jpereira.trainings.designpatterns.behavioral.observer.event.ApplianceEvent;
import eu.jpereira.trainings.designpatterns.behavioral.observer.observers.ApplianceEventObservable;
import eu.jpereira.trainings.designpatterns.behavioral.observer.observers.ApplianceEventObserver;

/**
 * @author windows
 * 
 * TODO Exercise: Implement the methods from {@link ApplianceEventObservable} here in this class
 */ 
public abstract class AbstractEventMapper implements EventMapper {

	private List<ApplianceEventObserver> observers;

	
	protected void updateObservers(ApplianceEvent event) {
		for ( ApplianceEventObserver observer : this.observers ) {
			observer.onApplianceEvent(event);
		}
	}
	public AbstractEventMapper() {
		observers = new ArrayList<ApplianceEventObserver>();
	}

	@Override
	public void addObserver(ApplianceEventObserver observer) {
		observers.add(observer);
	}

	@Override
	public void removeObserver(ApplianceEventObserver observer) {
		observers.remove(observer);
	}
	

}
