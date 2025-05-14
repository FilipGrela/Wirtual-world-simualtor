package logger;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class LogEntry {
    private final String message;
    private final LocalDateTime timestamp;

    public LogEntry(String message) {
        this.message = message;
        this.timestamp = LocalDateTime.now();
    }

    public String getMessage() {
        return message;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    @Override
    public String toString() {
        return "[" + timestamp.format(DateTimeFormatter.ofPattern("HH:mm:ss")) + "] " + message;
    }
}
