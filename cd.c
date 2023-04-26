#include "main.h"

/**
 * cd_dot - changes to the parent directory
 *
 * @data_sh: data relevant (environment)
 *
 * Return: no return
 */
void cd_dot(dt_shell *data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_sh);
	dir = data_sh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data_sh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	string_reverse(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			string_reverse(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data_sh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_sh);
	}
	data_sh->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @data_sh: data relevant (directories)
 * Return: no return
 */
void cd_to(dt_shell *data_sh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data_sh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data_sh, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_sh);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data_sh);

	free(cp_pwd);
	free(cp_dir);

	data_sh->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @data_sh: data relevant (environment)
 * Return: no return
 */
void cd_previous(dt_shell *data_sh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data_sh->_environment);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data_sh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data_sh);
	else
		set_env("PWD", cp_oldpwd, data_sh);

	p_pwd = _getenv("PWD", data_sh->_environment);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data_sh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @data_sh: data relevant (environment)
 * Return: no return
 */
void cd_to_home(dt_shell *data_sh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", data_sh->_environment);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data_sh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data_sh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data_sh);
	set_env("PWD", home, data_sh);
	free(p_pwd);
	data_sh->status = 0;
}
