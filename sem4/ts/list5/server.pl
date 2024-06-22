use HTTP::Daemon;
use HTTP::Status;

my $daemon = HTTP::Daemon->new(
    LocalAddr => "localhost",
    LocalPort => 4321,
) || die;

print "Running at: ", $daemon->url, "\n";

while (my $connection = $daemon->accept) {
    while (my $request = $connection->get_request) {
        if ($request->method ne "GET") {
            $connection->send_error(RC_FORBIDDEN);
            next;
        }

        my $uri = $request->uri;
        if ($uri->path eq "/header") {
            my $headers = $request->headers_as_string;
            my $response = HTTP::Response->new(200);
            $response->header("Content-Type" => "text/plain");
            $response->content("Your request's header is:\n\n" . $headers);
            $connection->send_response($response);
        } else {
            my $filename = $uri->path eq "/" ? "websites/index.html" : "websites" . $uri . ".html";
            $connection->send_file_response($filename);
        }
    }

    $connection->close;
    undef($connection);
}
