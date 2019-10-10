/*
 * events.cpp
 *
 *  Created on: Sep 22, 2019
 *      Author: pladams9
 */

#include <engine/Events.h>


namespace TF
{


/* METHOD DEFINITIONS */

// class Event
Event::Event()
: eventType("NULL_EVENT"), eventData({})
{}

Event::Event(EventType event_type, std::unordered_map<std::string, std::string> data, std::unordered_map<std::string, EntityID> entities)
: eventType(event_type), eventData(data), eventEntities(entities)
{}

EventType Event::GetEventType()
{
	return this->eventType;
}

std::string Event::GetStringData(std::string key)
{
	return this->eventData.at(key);
}

EntityID Event::GetEntityID(std::string key)
{
	return this->eventEntities.at(key);
}

// class EventQueue
EventQueue::EventQueue(EventManager* event_manager)
{
	this->eventManager = event_manager;
	this->eventManager->AddQueue(this);
}

EventQueue::~EventQueue()
{
	this->eventManager->RemoveQueue(this->queueID);
}

void EventQueue::Listen(EventType event_type)
{
	this->eventManager->AddListener(this->queueID, event_type);
}

bool EventQueue::PollEvents(Event& event_var)
{
	if(this->events.size() > 0)
	{
		event_var = this->events.front();
		this->events.pop();
		return true;
	}
	else
	{
		return false;
	}
}

// class EventManager
void EventManager::AddListener(EventQueueID queue_id, EventType event_type)
{
	this->listeners[event_type].insert(queue_id);
}

void EventManager::RemoveListener(EventQueueID queue_id, EventType event_type)
{
	if(this->listeners.find(event_type) != this->listeners.end())
	{
		this->listeners.at(event_type).erase(queue_id);
	}
}

void EventManager::TriggerEvent(Event event)
{
	if(this->listeners.find(event.GetEventType()) != this->listeners.end())
	{
		for(EventQueueID queue_id : this->listeners.at(event.GetEventType()))
		{
			this->queues.at(queue_id)->events.push(event);
		}
	}
}

void EventManager::AddQueue(EventQueue* event_queue)
{
	event_queue->queueID = this->nextQueueID++;
	this->queues.insert(std::pair<EventQueueID, EventQueue*>(event_queue->queueID, event_queue));
}

void EventManager::RemoveQueue(EventQueueID queue_id)
{
	this->queues.erase(queue_id);
}


}
