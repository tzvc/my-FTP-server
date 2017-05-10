/*
** protocol_ref.h for myftp in /home/rootkid/rendu/psu/PSU_2016_myftp
** 
** Made by theo champion
** Login   <theo.champion@epitech.eu>
** 
** Started on  Tue May  9 21:08:42 2017 theo champion
** Last update Wed May 10 14:43:31 2017 theo champion
*/

#ifndef PROTOCOL_REF_H
#define PROTOCOL_REF_H

#define T120 "Service ready in nnn minutes."
#define T125 "Data connection already open; transfer starting."
#define T150 "File status okay; about to open data connection."
#define T200 "Command okay."
#define T214 "Help message.On how to use the server or the \
meaning of a particularnon-standard command.  This reply is \
useful only to the human user."
#define T220 "Service ready for new user."
#define T221 "Service closing control connection.\nLogged out if appropriate."
#define T226 "Closing data connection.\nRequested file action \
successful (for example, file transfer or file abort)."
#define T227 "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."
#define T230 "User logged in, proceed."
#define T250 "Requested file action okay, completed."
#define T257 "\"PATHNAME\" created."
#define T331 "User name okay, need password."
#define T332 "Need account for login."
#define XXX "Error (RFC compliantx)"

static t_pair	g_pairs[] = {
  {110, "Restart marker replay."},
  {120, "Service ready in nnn minutes."},
  {125, "Data connection already open; transfer starting."},
  {150, "File status okay; about to open data connection."},
  {200, "The requested action has been successfully completed."},
  {202, "Command not implemented, superfluous at this site."},
  {211, "System status, or system help reply."},
  {212, "Directory status."},
  {213, "File status."},
  {214, "Help message. Explains how to use the server or the meaning \
of a particular non-standard command.				     \
 This reply is useful only to the human user."},
  {215, "NAME system type. Where NAME is an official system name from the"},
  {220, "Service ready for new user."},
  {221, "Service closing control connection."},
  {225, "Data connection open; no transfer in progress."},
  {226, "Closing data connection. Requested file action successful \
(for example, file transfer or file abort)."},
  {227, "Entering Passive Mode (h1,h2,h3,h4,p1,p2)."},
  {228, "Entering Long Passive Mode (long address, port)."},
  {229, "Entering Extended Passive Mode (|||port|)."},
  {230, "User logged in, proceed. Logged out if appropriate."},
  {231, "User logged out; service terminated."},
  {232, "Logout command noted, will complete when transfer done."},
  {234, "Specifies that the server accepts the authentication mechanism \
specified by the client, and the exchange of security data is complete. \
A higher level nonstandard code created by Microsoft"},
  {250, "Requested file action okay, completed."},
  {257, "\"PATHNAME\" created."},
  {300, "The command has been accepted, but the requested action is \
on hold, pending receipt of further information."},
  {331, "User name okay, need password."},
  {332, "Need account for login."},
  {350, "Requested file action pending further information"},
  {400, "The command was not accepted and the requested action did \
not take place, but the error condition is temporary and the action \
may be requested again."},
  {421, "Service not available, closing control connection. This may \
be a reply to any command if the service knows it must shut down."},
  {425, "Can't open data connection."},
  {426, "Connection closed; transfer aborted."},
  {430, "Invalid username or password"},
  {434, "Requested host unavailable."},
  {450, "Requested file action not taken."},
  {451, "Requested action aborted. Local error in processing."},
  {452, "Requested action not taken. Insufficient storage space \
in system.File unavailable (e.g., file busy)."},
  {500, "Syntax error, command unrecognized and the \
requested action did not take place. This may include errors \
such as command line too long."},
  {501, "Syntax error in parameters or arguments."},
  {502, "Command not implemented."},
  {503, "Bad sequence of commands."},
  {504, "Command not implemented for that parameter."},
  {530, "Not logged in."},
  {532, "Need account for storing files."},
  {534, "Could Not Connect to Server - Policy Requires SSL"},
  {550, "Requested action not taken. \
File unavailable (e.g., file not found, no access)."},
  {551, "Requested action aborted. Page type unknown."},
  {552, "Requested file action aborted. Exceeded storage \
allocation (for current directory or dataset)."},
  {553, "Requested action not taken. File name not allowed."},
  {600, "Replies regarding confidentiality and integrity"},
  {631, "Integrity protected reply."},
  {632, "Confidentiality and integrity protected reply."},
  {633, "Confidentiality protected reply."},
  {10000, "Common Winsock Error Codes"},
  {10054, "Connection reset by peer. The connection was \
forcibly closed by the remote host."},
  {10060, "Cannot connect to remote server."},
  {10061, "Cannot connect to remote server. The connection is \
actively refused by the server."},
  {10066, "Directory not empty."},
  {10068, "Too many users, server is full."}
};

#endif /* !PROTOCOL_REF_H */
