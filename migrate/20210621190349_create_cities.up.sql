CREATE TABLE cities (
    id bigserial not null primary key,
    name varchar not null,
    countryId bigserial not null
);