create table departments
(
    id             serial primary key,
    code           varchar(10)  not null,
    name           varchar(255) not null,
    research_count integer default 0
);


create table supervisors
(
    id             serial primary key,
    full_name      varchar(255)        not null,
    email          varchar(255) unique not null,
    phone          varchar(30) unique  not null,
    department     integer references departments (id),
    research_count integer default 0
);


create table students
(
    id         serial primary key,
    full_name  varchar(255)        not null,
    email      varchar(255) unique not null,
    phone      varchar(30) unique  not null,
    department integer references departments (id)
);


create table researches
(
    id           serial primary key,
    title        varchar(255) not null,
    department   integer references departments (id),
    field        varchar(255) not null,
    supervisor   integer references supervisors (id),
    url          varchar(500),
    funding_sum  integer default 0,
    report_count integer default 0
);


create table students_researches
(
    student_id  integer references students (id) on delete cascade   not null,
    research_id integer references researches (id) on delete cascade not null,
    primary key (student_id, research_id)
);


create table funding
(
    id       serial primary key,
    source   varchar(255),
    research integer references researches (id) on delete cascade not null,
    amount   integer,
    date     date
);


create table reports
(
    id       serial primary key,
    name     varchar(255)                                         not null,
    date     date,
    research integer references researches (id) on delete cascade not null
);

alter default privileges revoke all on functions from public;

--INDEXES
create index idx_researches_title on researches (title);
create index idx_students_name on students (lower(full_name));
create index idx_supervisors_name on supervisors using brin (full_name) with (pages_per_range =1);


--FUNCTIONS
create or replace function add_department(_code varchar(10), _name varchar(255))
    returns void as
$$
begin
    insert into departments (code, name) values (_code, _name);
end;
$$ language plpgsql;


create or replace function edit_department(_id integer, _code varchar(10), _name varchar(255))
    returns void as
$$
begin
    update departments set code = _code, name = _name where id = _id;
end;
$$ language plpgsql;


create or replace function delete_department(_id integer)
    returns void as
$$
begin
    delete from departments where id = _id;
end;
$$ language plpgsql;


create or replace function add_supervisor(_full_name varchar(255), _email varchar(255), _phone_number varchar(30),
                                          _department integer)
    returns void as
$$
begin
    insert into supervisors (full_name, email, phone, department)
    values (_full_name, _email, _phone_number, _department);
end;
$$ language plpgsql;


create or replace function edit_supervisor(_id integer, _full_name varchar(255), _email varchar(255),
                                           _phone_number varchar(30), _department integer)
    returns void as
$$
begin
    update supervisors
    set full_name  = _full_name,
        email      = _email,
        phone      = _phone_number,
        department = _department
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_supervisor(_id integer)
    returns void as
$$
begin
    delete from supervisors where id = _id;
end;
$$ language plpgsql;


create or replace function add_student(_full_name varchar(255), _email varchar(255), _phone_number varchar(30),
                                       _department integer)
    returns void as
$$
begin
    insert into students (full_name, email, phone, department)
    values (_full_name, _email, _phone_number, _department);
end;
$$ language plpgsql;


create or replace function edit_student(_id integer, _full_name varchar(255), _email varchar(255),
                                        _phone_number varchar(30), _department integer)
    returns void as
$$
begin
    update students
    set full_name  = _full_name,
        email      = _email,
        phone      = _phone_number,
        department = _department
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_student(_id integer)
    returns void as
$$
begin
    delete from students where id = _id;
end;
$$ language plpgsql;


create or replace function add_research(_title varchar(255), _department integer, _field varchar(255),
                                        _supervisor integer, _url varchar(500))
    returns void
    language plpgsql as
$$
begin
    insert into researches (title, department, field, supervisor, url)
    values (_title, _department, _field, _supervisor, _url);
end;
$$;


create or replace function edit_research(_id integer, _title varchar(255), _department integer, _field varchar(255),
                                         _supervisor integer, _url varchar(500))
    returns void as
$$
begin
    update researches
    set title      = _title,
        department = _department,
        field      = _field,
        supervisor = _supervisor,
        url        = _url
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_research(_id integer)
    returns void as
$$
begin
    delete from researches where id = _id;
end;
$$ language plpgsql;


create or replace function assign_research(_student integer, _research integer)
    returns void as
$$
begin
    insert into students_researches values (_student, _research);
end;
$$ language plpgsql;


create or replace function unassign_research(_student integer, _research integer)
    returns void as
$$
begin
    delete from students_researches where student_id = _student and research_id = _research;
end;
$$ language plpgsql;


create or replace function add_funding(_source varchar(255), _research integer, _amount integer, _date date)
    returns void as
$$
begin
    insert into funding (source, research, amount, date) values (_source, _research, _amount, _date);
end;
$$ language plpgsql;


create or replace function edit_funding(_id integer, _source varchar(255), _research integer, _amount integer,
                                        _date date)
    returns void as
$$
begin
    update funding
    set source   = _source,
        research = _research,
        amount   = _amount,
        date     = _date
    where id = _id;
end;
$$ language plpgsql;

create or replace function delete_funding(_id integer)
    returns void as
$$
begin
    delete from funding where id = _id;
end;
$$ language plpgsql;


create or replace function add_report(_name varchar(255), _date date, _research integer)
    returns void as
$$
begin
    insert into reports (name, date, research) values (_name, _date, _research);
end;
$$ language plpgsql;


create or replace function edit_report(_id integer, _name varchar(255), _date date,
                                       _research integer)
    returns void as
$$
begin
    update reports
    set name     = _name,
        date     = _date,
        research = _research
    where id = _id;
end;
$$ language plpgsql;


create or replace function delete_report(_id integer)
    returns void as
$$
begin
    delete from reports where id = _id;
end;
$$ language plpgsql;


create or replace function modify_department_research_count(_id integer, _dif integer)
    returns void as
$$
begin
    if _id is null then
        return;
    end if;

    update departments
    set research_count = research_count + _dif
    where id = _id;
end;
$$ language plpgsql;

create or replace function modify_supervisor_research_count(_id integer, _dif integer)
    returns void as
$$
begin
    if _id is null then
        return;
    end if;

    update supervisors
    set research_count = research_count + _dif
    where id = _id;
end;
$$ language plpgsql;

create or replace function modify_departments_supervisors_research_count()
    returns trigger as
$$
begin
    case tg_op
        when 'INSERT' then begin
            perform modify_department_research_count(new.department, 1);
            perform modify_supervisor_research_count(new.supervisor, 1);
        end;
        when 'DELETE' then begin
            perform modify_department_research_count(old.department, -1);
            perform modify_supervisor_research_count(old.supervisor, -1);
        end;
        end case;
    return new;
end;
$$ language plpgsql;


create or replace function modify_research_count(_table varchar, _id integer, _dif integer)
    returns void as
$$
begin
    case _table
        when 'departments' then perform modify_department_research_count(_id, _dif);
        when 'supervisors' then perform modify_supervisor_research_count(_id, _dif);
        end case;
end;
$$ language plpgsql;

create or replace function on_update_research()
    returns trigger as
$$
begin
    if old = new then
        return new;
    end if;

    if old.department <> new.department then
        perform modify_research_count('departments', old.department, -1);
        perform modify_research_count('departments', new.department, 1);
    end if;

    if old.supervisor <> new.supervisor then
        perform modify_research_count('supervisors', old.supervisor, -1);
        perform modify_research_count('supervisors', new.supervisor, 1);
    end if;

    return new;
end;
$$ language plpgsql;


create or replace function on_delete_department()
    returns trigger as
$$
begin
    update researches set department = null where department = old.id;
    update supervisors set department = null where department = old.id;
    update students set department = null where department = old.id;
    return old;
end;
$$ language plpgsql;


create or replace function on_delete_supervisor()
    returns trigger as
$$
begin
    update researches set supervisor = null where supervisor = old.id;
    return old;
end;
$$ language plpgsql;


create or replace function on_delete_student()
    returns trigger as
$$
begin
    delete from students_researches where student_id = old.id;
    return new;
end
$$ language plpgsql;


create or replace function on_insert_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum + new.amount where id = new.research;
    return new;
end
$$ language plpgsql;


create or replace function on_delete_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum - old.amount where id = old.research;
    return new;
end
$$ language plpgsql;


create or replace function on_update_funding()
    returns trigger as
$$
begin
    update researches set funding_sum = funding_sum - old.amount where id = old.research;
    update researches set funding_sum = funding_sum + new.amount where id = new.research;
    return new;
end
$$ language plpgsql;


create or replace function on_add_report()
    returns trigger as
$$
begin
    update researches set report_count = report_count + 1 where id = new.research;
    return new;
end;
$$ language plpgsql;


create or replace function on_edit_report()
    returns trigger as
$$

begin
    update researches set report_count = report_count + 1 where id = new.research;
    update researches set report_count = report_count - 1 where id = old.research;
    return new;
end;
$$ language plpgsql;


create or replace function on_delete_report()
    returns trigger as
$$
begin
    update researches set report_count = report_count - 1 where id = old.research;
    return new;
end
$$ language plpgsql;


--TRIGGERS
create trigger researches_insert_or_delete
    after insert or delete
    on researches
    for each row
execute function modify_departments_supervisors_research_count();


create trigger researches_update
    after update of department, supervisor
    on researches
    for each row
execute function on_update_research();


create trigger departments_delete
    before delete
    on departments
    for each row
execute function on_delete_department();


create trigger supervisors_delete
    before delete
    on supervisors
    for each row
execute function on_delete_supervisor();


create trigger students_delete
    after delete
    on students
    for each row
execute function on_delete_student();


create trigger funding_insert
    after insert
    on funding
    for each row
execute function on_insert_funding();


create trigger funding_delete
    after delete
    on funding
    for each row
execute function on_delete_funding();


create trigger funding_update
    after update
    on funding
    for each row
execute function on_update_funding();


create trigger reports_add
    after insert
    on reports
    for each row
execute function on_add_report();


create trigger reports_update
    after update
    on reports
    for each row
execute function on_edit_report();


create trigger reports_delete
    after delete
    on reports
    for each row
execute function on_delete_report();


-- TASKS
-- 3.a
create type statuses as
(
    Название               varchar(255),
    "Сумма финансирования" bigint,
    "Статус"               text
);
create or replace function get_research_statuses()
    returns setof statuses
as
$$
select r.title,
       sum(f.amount),
       case
           when sum(f.amount) = 0 then 'Без финансирования'
           when sum(f.amount) < 10000 then 'Небольшое финансирование'
           when sum(f.amount) < 50000 then 'Среднее финансирование'
           else 'Большое финансирование'
           end
from researches as r
         join funding as f on r.id = f.research
group by r.title;
$$ language sql;

-- 3.b
create view supervisors_view as
select s.*, d.name, d.code
from supervisors as s
         join departments as d on s.department = d.id;

create or replace function supervisors_view_insert()
    returns trigger
as
$$
declare
    dep_id integer;
begin
    if new.department is null then
        insert into departments (code, name) values (new.code, new.name) returning id into dep_id;
    else
        dep_id = new.department;
    end if;
    insert into supervisors (full_name, email, phone, department) values (new.full_name, new.email, new.phone, dep_id);
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_insert
    instead of insert
    on supervisors_view
    for each row
execute function supervisors_view_insert();


create or replace function supervisors_view_update()
    returns trigger
as
$$
begin
    update supervisors
    set full_name  = new.full_name,
        department = new.department
    where id = old.id;

    if old.department = new.department then
        update departments
        set code = new.code,
            name = new.name
        where id = old.department;
    end if;
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_update
    instead of update
    on supervisors_view
    for each row
execute function supervisors_view_update();


create or replace function supervisors_view_delete()
    returns trigger
as
$$
begin
    delete from supervisors where id = old.id;
    return null;
end
$$ language plpgsql;


create trigger on_supervisors_view_delete
    instead of delete
    on supervisors_view
    for each row
execute function supervisors_view_delete();


--3.c
create materialized view researches_view as
select r.title,
       r.field,
       r.url,
       r.funding_sum,
       r.report_count,
       d.code      as department,
       s.full_name as supervisor
from researches as r
         join departments d on d.id = r.department
         join supervisors s on d.id = s.department;


--3.d подзапрос в from
create or replace function info_researches()
    returns table
            (
                title     varchar(255),
                field     varchar(255),
                name      varchar(255),
                full_name varchar(255)
            )
as
$$
select title, field, res.name, res.full_name
from (select *
      from researches as r
               join departments d on d.id = r.department
               join supervisors s on d.id = s.department) as res
$$ language sql;


--3.e
create or replace function get_students()
    returns setof students
as
$$
select s.*
from students as s
where exists(select * from departments as d where d.id = s.department);
$$ language sql;


create or replace function get_dep_with_highest_funded_research()
    returns table
            (
                department_name         character varying,
                highest_funded_research character varying
            )
as
$$
select d.name    AS department_name,
       (select r.title
        FROM researches r
        WHERE r.department = d.id
        ORDER BY r.funding_sum DESC
        LIMIT 1) AS highest_funded_research
from departments d;
$$ language sql;


create or replace function get_students_research_count()
    returns table
            (
                student_name   character varying,
                research_count integer
            )
as
$$
SELECT s.full_name                                                        as student_name,
       (select count(*) from students_researches where student_id = s.id) as research_count
from students as s
$$ language sql;


--3.f
create or replace function count_funding_of_field()
    returns table
            (
                field character varying,
                sum   bigint
            )
as
$$
select r.field, sum(f.amount)
from funding as f
         join researches r on f.research = r.id
group by r.field
having sum(f.amount) > 0;
$$ language sql;


--3.g
create or replace function get_researches_with_min_count(_count integer)
    returns setof researches
as
$$
select *
from researches as r
where r.department = any (select d.id from departments d where d.research_count >= _count);
$$ language sql;


create or replace function get_productive_supervisors()
    returns setof supervisors
as
$$
select *
from supervisors as s
where s.research_count > all (select d.research_count from departments d);
$$ language sql;


--8
create or replace procedure set_dep_sup_on_research(_id integer, _department integer, _supervisors integer)
as
$$
begin
    begin
        update researches set supervisor = _supervisors, department = _department where id = _id;
        commit;
    exception
        when others then
            rollback;
            raise exception 'Ошибка изменения кафедры и руководителя: %', SQLERRM;
    end;
end
$$ language plpgsql;

--9
create or replace function clear_research_count(_dep integer)
    returns void as
$$
declare
    _curs refcursor;
    _rec  record;
begin
    open _curs for select * from supervisors where department = _dep;

    loop
        fetch next from _curs into _rec;
        exit when not found;
        update supervisors set research_count = 0 where current of _curs;
    end loop;

    close _curs;
end
$$ language plpgsql;



-- 10
create or replace function get_reports()
    returns setof reports
as
$$
select *
from reports
$$ language sql;


create or replace function get_funding_sum(_research integer)
    returns integer as
$$
select sum(amount)
from funding
where research = _research;
$$ language sql;


-- 12
create table olap
(
    id         serial primary key,
    title      varchar(255) not null,
    department varchar(255),
    field      varchar(255) not null,
    supervisor varchar(255),
    url        varchar(500),
    created_at timestamp default now()
);


create or replace function olap_trigger()
    returns trigger
as
$$
begin
    insert into olap (title, department, field, supervisor, url)
    values (new.title,
            (select code from departments where id = new.department),
            new.field,
            (select full_name from supervisors where id = new.supervisor),
            new.url);
    return new;
end
$$ language plpgsql;


create trigger research_inserted_for_olap
    after insert
    on researches
    for each row
execute function olap_trigger();


-- 11
create user admin with password 'admin';
create user student with password 'student';

create role admin_role;
create role student_role;

grant usage on all sequences in schema public to admin_role, student_role;

grant select on all tables in schema public to admin_role, student_role;
grant insert, update, delete on all tables in schema public to admin_role;
grant insert, update, delete on students, researches, students_researches, reports, olap to student_role;
grant update on departments, supervisors to student_role;

grant execute on all routines in schema public to admin_role;
grant execute on function
    add_student(varchar, varchar,varchar, integer),
    edit_student(integer, varchar, varchar, varchar, integer),
    delete_student(integer),

    add_research(varchar, integer, varchar, integer, varchar),
    edit_research(integer, varchar, integer, varchar, integer, varchar),
    delete_research(integer),

    add_report(varchar, date, integer),
    edit_report(integer, varchar, date, integer),
    delete_report(integer),

    assign_research(integer, integer),
    unassign_research(integer, integer),

    modify_department_research_count(integer, integer),
    modify_supervisor_research_count(integer, integer)
    to student_role;

grant admin_role to admin;
grant student_role to student;