import requests

class Request():
    body = []
    files = []
    cookies = []
    headers = []

    def __init__(self):
        """
            Set default values for request
        """

        self.method = "GET"
        self.url = None
        self.body_type = "body_data_form_data"
        self.body_raw = None
        self.authentication = None

    def add_body_item(self, body_item):
        """
            Add body item to list
        """

        self.body.append(body_item)

    def remove_body_item(self, body_item):
        """
            Remove body_item from list
        """

        self.body.remove(body_item)

    def add_cookie(self, cookie):
        """
            Add cookie to list
        """

        self.cookies.append(cookie)

    def remove_cookie(self, cookie):
        """
            Remove cookie from list
        """

        self.cookies.remove(cookie)

    def add_header(self, header):
        """
            Add header to list
        """

        self.headers.append(header)

    def remove_header(self, header):
        """
            Remove header from list
        """

        self.headers.remove(header)

    def get_body_form_data(self):
        """
            Get all enabled body_data key value pairs
        """

        body = {}

        for body_item in self.body:
            if body_item.is_active() and body_item.get_type() == "text":
                body[body_item.get_key()] = body_item.get_value()

        return body

    def get_body_files(self):
        """
            Get all enabled body_data files
        """

        files = []

        for file in self.body:
            if file.is_active() and file.get_type() == "file":
                files.append(file.get_file())

        return files

    def get_cookies(self):
        """
            Get all enabled cookies
        """

        cookies = {}

        for cookie in self.cookies:
            if cookie.is_active():
                cookies[cookie.get_key()] = cookie.get_value()

        return cookies

    def get_headers(self):
        """
            Get all enabled headers
        """

        headers = {}

        for header in self.headers:
            if header.is_active():
                headers[header.get_key()] = header.get_value()

        return headers

    def send_request(self, queue, callback):
        """
            Send request using the requests library
            in another thread to avoid locking the UI thread

            When the request is sent run the callback method
        """

        body = self.get_body_form_data()
        if self.body_type == "body_data_raw":
            body = self.body_raw

        request = requests.request(self.method, self.url, data = body,
                                    files = self.get_body_files(),
                                    headers = self.get_headers(),
                                    auth = self.authentication,
                                    cookies = self.get_cookies())

        self.response_code = request.status_code
        self.response_reason = request.reason
        self.response_headers = request.headers
        self.response_body = request.text

        queue.put(callback())
