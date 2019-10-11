/**
 * Events.h
 * --------
 *
 * Classes:
 *     Event         -  Has an event type, associated data (key/values), and associated entities (key/values)
 *     EventQueue    -  Can listen for certain event types; can be polled for pending events
 *     EventManager  -  Events are triggered to the manager and then distributed to associated listeners
 *
 */

#ifndef ENGINE_EVENTS_H_
#define ENGINE_EVENTS_H_


/* INCLUDES */
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "engine/Entity.h"


namespace TF
{


/* FORWARD DECLARATIONS */
class EventManager;


/* TYPEDEFS */
using EventType = std::string;
using EventQueueID = unsigned int;


/* CONSTANTS */
const EventQueueID NULL_EVENT_QUEUE = 0;


/* CLASS DEFINITIONS */
class Event
{
public:
	Event();
	Event(
			EventType event_type,
			std::unordered_map<std::string, std::string> data = {},
			std::unordered_map<std::string, EntityID> entities = {}
	);

	EventType GetEventType() const;
	std::string GetStringData(std::string key) const;
	EntityID GetEntityID(std::string key) const;

private:
	EventType _eventType;
	std::unordered_map<std::string, std::string> _eventData;
	std::unordered_map<std::string, EntityID> _eventEntities;
};


class EventQueue
{
	friend class EventManager;

public:
	EventQueue(EventManager* event_manager);
	~EventQueue();

	void Listen(const EventType event_type);
	bool PollEvents(Event& event_var);

private:
	EventManager* _eventManager;
	EventQueueID _queueID = NULL_EVENT_QUEUE;
	std::queue<Event> _events;
};


class EventManager
{
public:
	void AddListener(const EventQueueID queue_id, const EventType event_type);
	void TriggerEvent(const Event event);

	void AddQueue(EventQueue* event_queue);
	void RemoveQueue(const EventQueueID queue_ID);

private:
	std::unordered_map<EventQueueID, EventQueue*> _queues;
	EventQueueID _nextQueueID = NULL_EVENT_QUEUE + 1;
	std::unordered_map<EventType, std::unordered_set<EventQueueID>> _listeners;
};

}


#endif /* ENGINE_EVENTS_H_ */
