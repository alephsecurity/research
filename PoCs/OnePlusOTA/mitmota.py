URL = "<url>"
MD5 = "<md5>"
SIZE= "<size>"

def response(flow):
  if "h2os" in flow.request.pretty_url or "coloros" in flow.request.pretty_url:
    print(flow.request.pretty_url)
    flow.response.status_code=200
    flow.response.headers["Content-Type"] = "application/json;charset=UTF-8"
    flow.response.headers["Connection"] = "close"
    flow.response.content = b"{\"type\":\"1\",\
                               \"wipe\":\"0\",\
                               \"new_version\":\"foo\",\
                               \"version_name\":\"foo!\",\
                               \"description\":\"foo\",\
                               \"extract\":\"foo\",\
                               \"patch_name\":\"foo.zip\",\
                               \"patch_md5\":\"%s\",\
                               \"patch_size\":\"%s\",\
                               \"down_url\":\"%s\",\
                               \"active_url\":\"%s\",\
                               \"recommend\":\"100\",\
                               \"share\":\"foo\"}" % (MD5, SIZE, URL, URL)
