// Big Header

/** */
__attribute__((hot)) int Core_request(
	int request,
	void *response
)
{
	switch (request) {
		case 0:
			// Handle request 0
			break;
		case 1:
			// Handle request 1
			break;
		default:
			return -1; // Unknown request
	}
}