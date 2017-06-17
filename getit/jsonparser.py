import pickle

class JsonParser:

    def write_file(
            body_method,
            body_url,
            body_selected_data,
            body_data_form,
            body_data_raw_language,
            body_data_raw,
            auth_selected,
            auth_basic_username,
            auth_basic_password,
            auth_digest_username,
            auth_digest_password,
            cookies,
            headers,
            filename):
        """
            Write json to binary file
        """

        request = {
            'body': {
                'method': body_method,
                'url': body_url,
                'selected_data': body_selected_data,
                'form': body_data_form,
                'raw_language': body_data_raw_language,
                'raw': body_data_raw
            },
            'authentication': {
                'selected': auth_selected,
                'basic': {
                    'username': auth_basic_username,
                    'password': auth_basic_password
                },
                'digest': {
                    'username': auth_digest_username,
                    'password': auth_digest_password
                }
            },
            'cookies': cookies,
            'headers': headers
        }

        with open(JsonParser.correct_filename(filename), 'wb') as file:
            pickle.dump(request, file, pickle.HIGHEST_PROTOCOL)

    def read_file(filename):
        """
            Open binary file
        """

        with open(filename, 'rb') as file:
            return pickle.load(file)

    def correct_filename(filename):
        """
            Check if the filename ends with .getit if it's not the
            case then add it to the filename
        """

        if not filename.endswith('.getit'):
            filename += '.getit'

        return filename
