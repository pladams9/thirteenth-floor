/*
 * events.h
 *
 *  Created on: Sep 22, 2019
 *      Author: pladams9
 */

#ifndef ENGINE_EVENTS_H_
#define ENGINE_EVENTS_H_


/* INCLUDES */
#include <Entity.h>
#include <string>
#include <unordered_map>
#include <queue>
#include <unordered_set>



namespace TF
{


/* FORWARD DECLARATIONS */
class EventManager;


/* TYPEDEFS */
using EventType = std::string;
using EventQueueID = unsigned int;


/* CLASS DEFINITIONS */
class Event
{
private:
	EventType eventType;
	std::unordered_map<std::string, std::string> eventData;
	std::unordered_map<std::string, EntityID> eventEntities;
public:
	Event();
	Event(
			EventType event_type,
			std::unordered_map<std::string, std::string> data = {},
			std::unordered_map<std::string, EntityID> entities = {}
	);
	EventType GetEventType();
	std::string GetStringData(std::string key);
};

class EventQueue
{
	friend class EventManager;
private:
	EventManager* eventManager;
	EventQueueID queueID = 0;
	std::queue<Event> events;
public:
	EventQueue(EventManager* event_manager);
	~EventQueue();

	void Listen(EventType event_type);
	bool PollEvents(Event& event_var);
};

class EventManager
{
private:
	std::unordered_map<EventQueueID, EventQueue*> queues;
	EventQueueID nextQueueID = 1;
	std::unordered_map<EventType, std::unordered_set<EventQueueID>> listeners;
public:
	void AddListener(EventQueueID queue_id, EventType event_type);
	void RemoveListener(EventQueueID queue_id, EventType event_type);

	void TriggerEvent(Event event);

	void AddQueue(EventQueue* event_queue);
	void RemoveQueue(EventQueueID queue_id);
};

}


#endif /* ENGINE_EVENTS_H_ */
