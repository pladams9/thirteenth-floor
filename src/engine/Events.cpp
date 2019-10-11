/**
 * Events.cpp
 * ----------
 *
 */

#include "engine/Events.h"


namespace TF
{


/* METHOD DEFINITIONS */

// class Event
Event::Event()
: _eventType("NULL_EVENT"), _eventData({})
{}

Event::Event(EventType event_type, std::unordered_map<std::string, std::string> data, std::unordered_map<std::string, EntityID> entities)
: _eventType(event_type), _eventData(data), _eventEntities(entities)
{}

EventType Event::GetEventType() const
{
	return _eventType;
}

std::string Event::GetStringData(std::string key) const
{
	auto it = _eventData.find(key);
	if(it != _eventData.end()) return (*it).second;
	else return "";
}

EntityID Event::GetEntityID(std::string key) const
{
	auto it = _eventEntities.find(key);
	if(it != _eventEntities.end()) return (*it).second;
	else return NULL_ENTITY;
}


// class EventQueue
EventQueue::EventQueue(EventManager* event_manager)
: _eventManager(event_manager)
{
	_eventManager->AddQueue(this);
}

EventQueue::~EventQueue()
{
	_eventManager->RemoveQueue(_queueID);
}

void EventQueue::Listen(const EventType event_type)
{
	_eventManager->AddListener(_queueID, event_type);
}

bool EventQueue::PollEvents(Event& event_var)
{
	if(this->_events.size() > 0)
	{
		event_var = this->_events.front();
		this->_events.pop();
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
	_listeners[event_type].insert(queue_id);
}

void EventManager::TriggerEvent(Event event)
{
	if(_listeners.find(event.GetEventType()) != _listeners.end())
	{
		for(EventQueueID queue_id : _listeners.at(event.GetEventType()))
		{
			_queues.at(queue_id)->_events.push(event);
		}
	}
}

void EventManager::AddQueue(EventQueue* event_queue)
{
	event_queue->_queueID = _nextQueueID++;
	_queues.insert(std::pair<EventQueueID, EventQueue*>(event_queue->_queueID, event_queue));
}

void EventManager::RemoveQueue(EventQueueID queue_id)
{
	_queues.erase(queue_id);
	for(auto it : _listeners)
	{
		it.second.erase(queue_id);
	}
}


}
