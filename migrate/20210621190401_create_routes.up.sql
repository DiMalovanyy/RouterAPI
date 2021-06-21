CREATE TABLE routes (
    id bigserial not null primary key,
    sourceFromId bigserial not null,
    destinationId bigserial not null,

    passangerId bigserial not null,
    vehicleId bigserial not null
);