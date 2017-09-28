#include "session.h"

static int menu_admin(session_t *s) {
	switch (s->level) {
		case 1: //main menu
			{
				puts("---- Admin menu ----");
				printf("1. List all employees\n2. Add an employee\n3. Delete an employee\
						\n4. Change admin password\n5. Quit\nYour selection: ");
				scanf("%d", &s->level);
				break;
			}
		case 2: //add an employee
			{
				entry_user_t *new = malloc(sizeof(entry_user_t));
				if (!new) {
					return -1;
				}
				puts("---- Add an employee ----");
				printf("username: ");
				scanf("%s", new->username);
				printf("password: ");
				scanf("%s", new->password);
#ifdef __DEBUG__
				P_DEBUG("%s", "Done reading, writing changes into database\n");
#endif
				db_add_user(s->db_e, new);
				db_save_user(s->db_e, "employees.dat");

				//reset menu level
				s->level = 1;
				break;
			}

		case 3: //delete an employee
			{
				char username[100];
				puts("---- Delete an employee ----");
				printf("username: ");
				scanf("%s", username);

#ifdef __DEBUG__
				P_DEBUG("Finding \"%s\" in database\n", username);
#endif
				db_remove_user(s->db_e, username);
				db_save_user(s->db_e, "employees.dat");

				s->level = 1;
				break;
			}

		case 4: //change admin password
			{
				char password[100];
				puts("---- Change my password ----");
				//to do: check old password
				printf("new password: ");
				scanf("%s", password);
#ifdef __DEBUG__ 
				P_DEBUG("Done reading, looking up for admin %s in database\n",
						s->user->username);
#endif


#ifdef __DEBUG__ 
				P_DEBUG("%s", "Writing changes into database\n");
#endif
				user_change_password(s->user)

				s->level = 1;
				break;
			}

		case 5: //quit
			{
				s->level = 0;
				return 0;
			}
	}
	return 0;
}

static inline int menu_employee(session_t *s) {
	return 0;
}

void menu(session_t *s) {
	if (s->type == U_ADMIN) {
		while (s->level != 0) 
			menu_admin(s);
	}
	else if (s->type == U_EMPLOYEE) {
		while (s->level != 0) {
			menu_employee(s);
		}
	}
}