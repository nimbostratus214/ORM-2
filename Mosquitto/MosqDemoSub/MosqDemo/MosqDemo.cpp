// Subscriber
#include <mosquitto.h>
#include <stdio.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
	if (rc == 0) {
		printf("****************** Subcribing to topics ****************** \n ");
		mosquitto_subscribe(mosq, NULL, "bolnica/prizemlje", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/eksterijer/ulaz/brightness_sensor", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/eksterijer/ulaz/temp_sensor1", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/prvi_sprat/ordinacija2/security_cam", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/prvi_sprat/doc_room/smoke_sensor", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/prvi_sprat/hodnik/smart_door", 0);
		mosquitto_subscribe(mosq, NULL, "pametnaBolnica/drugi_sprat/soba2/bed_sensor", 0);


	} else {
		mosquitto_disconnect(mosq);
	}
}



void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	// Print the topic for the first message received, then disconnect
	
		printf("Topic: %s\n", msg->topic);
		printf("State: %s\n", msg->payload);
		printf("\n");
		//mosquitto_disconnect(mosq);
}

int main()
{
	struct mosquitto *mosq;
	int rc;

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL, true, NULL);
	if (mosq == NULL) {
		printf("Failed to create client instance.\n");
		return 1;
	}
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);



	rc = mosquitto_connect(mosq, "147.91.160.65", 1883, 60); //192.168.0.11
	if (rc != MOSQ_ERR_SUCCESS) {
		printf("Connect failed: %s\n", mosquitto_strerror(rc));
		return 1;
	}

	mosquitto_loop_forever(mosq, -1, 1);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
}