// Publisher
#include <stdio.h>
#include <mosquitto.h>
#include <Windows.h>

int main() {
	int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new("publisher-test", true, NULL);

	rc = mosquitto_connect(mosq, "localhost", 1883, 60);
	if (rc != 0) {
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		return -1;
	}

	printf("We are now connected to the broker!\n");

	while (1) {
		printf("Poruka poslata -> Tema: bolnica/prizemlje | Opis: Trenutna temperatura prostorije je 25C.\n");
		mosquitto_publish(mosq, NULL, "bolnica/prizemlje", 4, "25C", 0, false);
		printf("Poruka poslata -> Tema: pametnaBolnica/eksterijer/ulaz/brightness_sensor | Opis: Nivo svetlosti na ulazu je 77%\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/eksterijer/ulaz/brightness_sensor", 4, "77%", 0, false);
		printf("Poruka poslata -> Tema: pametnaBolnica/eksterijer/ulaz/temp_sensor1 | Opis: Trenutna temperatura prostorije je 33C.\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/eksterijer/ulaz/temp_sensor1", 4, "33C", 0, false);
		printf("Poruka poslata -> Tema: pametnaBolnica / prvi_sprat / ordinacija2 / security_cam | Opis: Sigurnosna kamera je aktivna.\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/prvi_sprat/ordinacija2/security_cam", 3, "ON", 0, false);
		printf("Poruka poslata -> Tema: pametnaBolnica/prvi_sprat/doc_room/smoke_sensor | Opis: Senzor dima je aktivan.\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/prvi_sprat/doc_room/smoke_sensor", 3, "ON", 0, false);

		printf("Poruka poslata -> Tema: pametnaBolnica/prvi_sprat/hodnik/smart_door | Opis: Pametna vrata aktivirana.\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/prvi_sprat/hodnik/smart_door", 8, "In use!", 0, false);

		printf("Poruka poslata -> Tema: pametnaBolnica/drugi_sprat/soba2/bed_sensor | Opis: Nema pacijenta na krevetu.\n");
		mosquitto_publish(mosq, NULL, "pametnaBolnica/drugi_sprat/soba2/bed_sensor", 17, "Nema pacijenata!", 0, false);
		
		printf("\n");
		Sleep(3000);
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	//mosquitto_loop_forever(mosq, -1, 1);

	//mosquitto_disconnect(mosq);
	//mosquitto_destroy(mosq);
	//mosquitto_lib_cleanup();

	return 0;
}